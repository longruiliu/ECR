#include "logindialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);
}

loginDialog::~loginDialog()
{
    delete ui;
}


void loginDialog::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}
void loginDialog::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}

void loginDialog::on_configBtn_clicked()
{
    LoginConfig *logconf=new LoginConfig();
    logconf->show();

    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::on_LoginBtn_clicked()
{
    ChatRoomPanel *crp = new ChatRoomPanel();
    crp->show();

    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::on_registerBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    RegisterDialog *rd = new RegisterDialog();
    rd->show();
}
