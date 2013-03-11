#include "loginconfig.h"
#include "ui_loginconfig.h"

LoginConfig::LoginConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginConfig),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);
}

LoginConfig::~LoginConfig()
{
    delete ui;
}

void LoginConfig::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}
void LoginConfig::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}

void LoginConfig::on_okBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    loginDialog *ld = new loginDialog();
    ld->show();

    serverIP = ui->serverIPText->text();
    serverPort = ui->serverPortText->text();
}

void LoginConfig::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}
