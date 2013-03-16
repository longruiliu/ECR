#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"
#include "protocol/protocol.h"
#include "networkqueue.h"
#include "msgRecord.h"
#include "friendlist.h"
#include "protocol_const.h"
#include <QTimer>
#include <vector>
#include <QWebFrame>
#include "logindialog.h"

GroupChatDialog::GroupChatDialog(int groupID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDialog),
    fadeEffect(this),
    shakeEffect(this),
    lastMsgTime(0)
{
    currentGroupID=groupID;

    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);

    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));

    QFile file(":/chatStyle.html");
    if(!file.open(QIODevice::ReadOnly))
    {
        //chatStyle.html doesn't exsit
        messageList="";
    }
    else
    {
        messageList = file.readAll();
        ui->messageListWebView->setHtml(messageList);
    }
    file.close();

    getMemberList();
    getGroupMsg();
}

GroupChatDialog::~GroupChatDialog()
{
    delete ui;
    emit closeDialog(currentGroupID);
}

void GroupChatDialog::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}
void GroupChatDialog::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}


void GroupChatDialog::raiseChatDialog()
{
    fadeEffect.raiseDialog();
}

void GroupChatDialog::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT);
}

void GroupChatDialog::addFriendTolist(int friendid, QString nickname)
{
    friendIDList.push_back(friendid);

    QListWidgetItem *friend1 = new QListWidgetItem(ui->FriendListWidget);
    friend1->setIcon(QIcon(":/header/1.png"));
    friend1->setText(nickname);
    friend1->setTextAlignment(Qt::AlignLeft);
    friend1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

}

void GroupChatDialog::handleChatRoomClose(int friendID)
{
    delete chatRoomMap[friendID];
    chatRoomMap.remove(friendID);
}

void GroupChatDialog::startChatWithSelectedFriend(int friendid)
{
    if(0==friendid)
        friendid= friendIDList[ui->FriendListWidget->currentRow()];

    if(chatRoomMap.contains(friendid))
    {
        chatRoomMap[friendid]->raiseChatDialog();
    }
    else
    {
        chatRoomMap[friendid]=new chatRoom(friendid);
        chatRoomMap[friendid]->show();

        connect(chatRoomMap[friendid],SIGNAL(closeDialog(int)),
                this,SLOT(handleChatRoomClose(int)));
    }
}

void GroupChatDialog::AddMessageToList(QString mcontent, QString authorName,time_t postTime,int senderType)
{
    if(senderType < 0)
        messageList+=tr("<p class=\"Me\"></p><p class=\"isaid\"><strong>[");
    else if(senderType > 0)
        messageList+=tr("<p class=\"U\"></p><p class=\"usaid\">[<strong>");
    else
        messageList+=tr("<p class=\"root\"></p><p class=\"rootsaid\">[<strong>");
    messageList+=authorName;
    messageList+=tr(":");
    QDateTime ti;
    ti.setTime_t(postTime);
    messageList+=ti.toString("hh:mm:ss dd-MM-yyyy");
    messageList+="]</strong></br>";
    messageList+=mcontent;
    messageList+=tr("</p><div class=\"clear\"></div>");
    ui->messageListWebView->setHtml(messageList+"</div></body>",
                                    QUrl(QCoreApplication::applicationDirPath()+"//"));
    QWebFrame* mf = ui->messageListWebView->page()->mainFrame();
    mf->setScrollBarValue(Qt::Vertical, mf->scrollBarMaximum(Qt::Vertical));
    qDebug() <<"Frame position"<< mf->scrollBarMaximum(Qt::Vertical);
}

void GroupChatDialog::on_SendMessageBtn_clicked()
{
    std::string str;
    Nevent ev;

    sendText=ui->SendMessageText->toPlainText();

    if(sendText.isEmpty())
        return;

    ui->SendMessageText->clear();

    str.clear();
    str.insert(0,"group");
    ev.req.setType(str);

    str.clear();
    str.insert(0,"sendmsg");
    ev.req.setMethod(str);

    ev.req.addParams(currentGroupID);

    str.clear();
    str.insert(0, sendText.toLocal8Bit().data());
    ev.req.addParams(str);
    ev.callee = this;
    strcpy(ev.signal, SLOT(sendGroupMessageResponse(Response)));

    nq.pushEvent(ev);

}
void GroupChatDialog::sendGroupMessageResponse(Response resp){

}

void GroupChatDialog::receiveGroupMsg(Response resp)
{
    std::vector<msgRecord> mList;
    std::vector<msgRecord>::iterator i;
    resp.getMsgList(mList);
    for (i = mList.begin(); i != mList.end(); i++)
    {
        if (i->msgType == MSG_TYPE_GROUP_RED)
            AddMessageToList(i->msgText.c_str(),FriendList::getNickname(i->srcID),i->postTime, 0);
        else if (i->srcID == myUserID)
            AddMessageToList(i->msgText.c_str(),FriendList::getNickname(i->srcID),i->postTime, -1);
        else
            AddMessageToList(i->msgText.c_str(),FriendList::getNickname(i->srcID),i->postTime, 1);
    //    ui->MessageListWidget->addItem(i->msgText.c_str());
        if (i->postTime > lastMsgTime)
            lastMsgTime = i->postTime;
    }
}

void GroupChatDialog::receiveMemberList(Response resp)
{
    UserList ul;
    resp.getUserList(ul);
    for (UserList::iterator i=ul.begin(); i!=ul.end(); i++)
        addFriendTolist(*i,FriendList::getNickname(*i));
}

void GroupChatDialog::getGroupMsg()
{
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0, "group");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "fetchmsg");
    ev.req.setMethod(str);
    ev.callee = this;
    ev.req.addParams(currentGroupID);
    ev.req.addParams(lastMsgTime);
    strcpy(ev.signal, SLOT(receiveGroupMsg(Response)));
    nq.pushEvent(ev);
}

void GroupChatDialog::getMemberList()
{
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0, "group");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "userlist");
    ev.req.setMethod(str);
    ev.callee = this;
    ev.req.addParams(currentGroupID);
    strcpy(ev.signal, SLOT(receiveMemberList(Response)));
    nq.pushEvent(ev);
}

void GroupChatDialog::on_shakeBtn_clicked()
{
    shakeEffect.startShake();
}
