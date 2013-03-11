#include "registerdialog.h"
#include "ui_registerdialog.h"

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}
void RegisterDialog::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}

void RegisterDialog::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void RegisterDialog::on_OkBtn_clicked()
{
    userName=ui->userNameEdit->text();
    userPassword1=ui->userPsw1Edit->text();
    userPassword2=ui->userPsw2Edit->text();
    userNickName=ui->userNickNameEdit->text();

    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    loginDialog *ld = new loginDialog();
    ld->show();
}

