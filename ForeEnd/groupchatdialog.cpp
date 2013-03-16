#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"

GroupChatDialog::GroupChatDialog(int groupID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDialog),
    fadeEffect(this),
    shakeEffect(this)
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

void GroupChatDialog::AddMessageToList(QString mcontent, QString authorName, bool isSelf)
{
    if(isSelf)
        messageList+=tr("<p class=\"Me\"></p><p class=\"isaid\"><strong>[");
    else
        messageList+=tr("<p class=\"U\"></p><p class=\"usaid\">[<strong>");
    messageList+=authorName;
    messageList+=tr(":]</strong></br>");
    messageList+=mcontent;
    messageList+=tr("</p><div class=\"clear\"></div>");
    ui->messageListWebView->setHtml(messageList+"</div></body>",
                                    QUrl(QCoreApplication::applicationDirPath()+"//"));
}

void GroupChatDialog::on_SendMessageBtn_clicked()
{
    sendText=ui->SendMessageText->toPlainText();

    if(!sendText.isEmpty())
    {
       //Send Text To Server

        AddMessageToList(sendText,tr("Your Nick Name"),true);

        //Auto Replay
        AddMessageToList(tr("Auto Replay"),tr("Friend's Nick Name"),false);
    }

    ui->SendMessageText->clear();
}

void GroupChatDialog::receiveResponse(Response resp)
{

}

void GroupChatDialog::on_shakeBtn_clicked()
{
    shakeEffect.startShake();
}
