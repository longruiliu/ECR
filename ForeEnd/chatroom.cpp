#include "chatroom.h"
#include "ui_chatroom.h"
#include <QFile>

chatRoom::chatRoom(QWidget *parent) :
    QDialog(parent),ui(new Ui::chatRoom),fadeEffect(this),shakeEffect(this)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    fadeEffect.startFadeInOut(FADEIN);

    QFile file("chatStyle.html");
    if(!file.open(QIODevice::ReadOnly))
    {
        exit(1);
    }
    messageList = file.readAll();
    ui->messageListWebView->setHtml(messageList);
}

chatRoom::~chatRoom()
{
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

void chatRoom::on_SendButton_clicked()
{
    QString sendText = ui->SendTextEdit->toPlainText();

    if(!sendText.isEmpty())
    {
       //将文本发往服务器

        AddMessageToList(sendText,tr("孤舟一叶"),true);

        //自动回复
        AddMessageToList(tr("这是自动回复"),tr("好友昵称"),false);
    }

    ui->SendTextEdit->clear();
}

void chatRoom::on_CloseWinBtn_clicked()
{
    //窗口淡出
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
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
    ui->messageListWebView->setHtml(messageList+"</div></body>",QUrl("file:///D:/ECR/USay-build-desktop/" ));
}

void chatRoom::on_shakeBtn_clicked()
{
    //抖动窗口
    shakeEffect.startShake();
}
