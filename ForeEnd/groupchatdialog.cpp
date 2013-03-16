#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"
#include "protocol/protocol.h"
#include "networkqueue.h"
#include "msgRecord.h"
#include "protocol_const.h"
#include <QTimer>
#include <vector>

GroupChatDialog::GroupChatDialog(int groupID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDialog),
    fadeEffect(this),lastMsgTime(0)
{
    currentGroupID=groupID;

    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);

    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));
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

void GroupChatDialog::on_SendMessageBtn_clicked()
{
    std::string str;
    Nevent ev;

    sendText=ui->SendMessageText->toPlainText();

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

    nq.pushEvent(ev);

}

void GroupChatDialog::receiveGroupMsg(Response resp)
{
    std::vector<msgRecord> mList;
    std::vector<msgRecord>::iterator i;
    resp.getMsgList(mList);
    for (i = mList.begin(); i != mList.end(); i++)
    {
        if (i->msgType == MSG_TYPE_GROUP_RED)
        {
        }
        ui->MessageListWidget->addItem(i->msgText.c_str());
        if (i->postTime > lastMsgTime)
            lastMsgTime = i->postTime;
    }
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
