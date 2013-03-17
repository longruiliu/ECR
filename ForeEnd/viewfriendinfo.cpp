#include "viewfriendinfo.h"
#include "ui_viewfriendinfo.h"

ViewFriendInfo::ViewFriendInfo(QString nickName,QString userInfo,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewFriendInfo),
    fadeEffect(this)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    fadeEffect.startFadeInOut(FADEIN);

    ui->friendNickNameText->setText(nickName);
    ui->friendInfoText->setText(userInfo);
}

ViewFriendInfo::~ViewFriendInfo()
{
    delete ui;
}

void ViewFriendInfo::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}
void ViewFriendInfo::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void ViewFriendInfo::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

