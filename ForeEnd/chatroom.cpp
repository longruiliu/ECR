#include "chatroom.h"
#include "ui_chatroom.h"
#include <QFile>
#include "networkqueue.h"
#include "friendlist.h"
#include "QWebFrame"

chatRoom::chatRoom(int friendid,QWidget *parent) :
    QDialog(parent),ui(new Ui::chatRoom),fadeEffect(this),shakeEffect(this)
{
    currentFriendID=friendid;
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    fadeEffect.startFadeInOut(FADEIN);

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

    timeStamp = 0;
}

chatRoom::~chatRoom()
{
    emit closeDialog(currentFriendID);
    delete ui;
}

void chatRoom::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}

void chatRoom::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}

void chatRoom::raiseChatDialog()
{
    fadeEffect.raiseDialog();
}

void chatRoom::on_SendButton_clicked()
{
    sendText = ui->SendTextEdit->toPlainText();

    if(!sendText.isEmpty())
    {
       //Send Text To Server
        Nevent ev;
        std::string str;

        str.clear();
        str.insert(0,"regular");
        ev.req.setType(str);

        str.clear();
        str.insert(0, "sendmsg");
        ev.req.setMethod(str);

        ev.req.addParams(this->currentFriendID);

        str.clear();
        str.insert(0, sendText.toLocal8Bit().data());
        ev.req.addParams(str);

        ev.callee = this;
        strcpy(ev.signal, SLOT(receiveMessageResponse(Response)));

        nq.pushEvent(ev);

        AddMessageToList(sendText,FriendList::getNickname(this->currentFriendID),true);
    }


}

void chatRoom::on_CloseWinBtn_clicked()
{
    //Fade In Fade Out
    fadeEffect.startFadeInOut(FADEOUT_HIDE);
}

void chatRoom::AddMessageToList(QString mcontent, QString authorName, bool isSelf)
{
    if(isSelf)
        messageList+=tr("<p class=\"Me\"></p><p class=\"isaid\"><strong>[");
    else
        messageList+=tr("<p class=\"U\"></p><p class=\"usaid\">[<strong>");
    messageList+=authorName;
    messageList+=tr(":]</strong></br>");
    messageList+=mcontent;
    messageList+=tr("</p><div class=\"clear\"></div>");
    ui->messageListWebView->setHtml(messageList+"<a id='butt'></a></div></body>",
                                    QUrl(QCoreApplication::applicationDirPath()+"//"));
    QWebFrame* mf = ui->messageListWebView->page()->mainFrame();
    mf->scrollToAnchor("butt");
}

void chatRoom::on_shakeBtn_clicked()
{
    //Shake Dialog
    shakeEffect.startShake();
}


void chatRoom::receiveMessageResponse(Response resp)
{
    if(resp.getStatus() >0){
        AddMessageToList(QString("Send message Failed"),
                         FriendList::getNickname(this->currentFriendID), true);
    }else{
        ui->SendTextEdit->clear();
    }
}
