#include "userinfoconfig.h"
#include "ui_userinfoconfig.h"

UserInfoConfig::UserInfoConfig(QString userName, QString NickName, QString userInfo, QWidget *parent):
    QDialog(parent),
    ui(new Ui::UserInfoConfig),
    fadeEffect(this)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    fadeEffect.startFadeInOut(FADEIN);
    this->userNickName=NickName;
    this->userInfo=userInfo;
    ui->userNameEdit->setText(userName);
    ui->userNickNameEdit->setText(NickName);
    ui->userInfoEdit->setText(userInfo);
}

UserInfoConfig::~UserInfoConfig()
{
    delete ui;
}

void UserInfoConfig::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();
    this->mousePos = event->globalPos();
    this->dPos = mousePos - windowPos;
}
void UserInfoConfig::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void UserInfoConfig::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

