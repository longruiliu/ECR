#include "logindialog.h"
#include "ui_logindialog.h"
#include "protocol/protocol.h"
#include <string.h>

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);

    conf = new LoginConfig();
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
    conf->StartFadeIn();
    conf->show();
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::on_LoginBtn_clicked()
{

    Nevent ev;
    std::string str;
    //send login request

    //We must get server IP and port from loginconfig
    if(conf->serverIP.isEmpty() || conf->serverPort.isEmpty()){
        qDebug() << "We must configure server IP and port first" << endl;
        return;
    }
    nq->setRemote(conf->serverIP, conf->serverPort);
    //ml also needs sessoinID if you want it works.
    ml->setRemote(conf->serverIP, conf->serverPort);

    ev.req.setSessionID(0);
    str.insert(0, "regular");
    ev.req.setType(str);
    userName = ui->NamelineEdit->text();
    userPassword = ui->PswlineEdit->text();
    qDebug() << userName << userPassword << endl;
    str.clear();
    str.insert(0,"login");
    ev.req.setMethod(str);

    ev.req.addParams(userName.toInt());

    str.clear();
    str.insert(0, userPassword.toLocal8Bit().data());
    ev.req.addParams(str);

    ev.callee = (QObject *)this;
    strcpy(ev.signal, SLOT(receiveLoginResponse(Response)));

    nq->pushEvent(ev);

    conf->close();

}

void loginDialog::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    conf->close();
}

void loginDialog::on_registerBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    RegisterDialog *rd = new RegisterDialog();
    rd->show();
}

void loginDialog::receiveLoginResponse(Response resp)
{
    qDebug() << "received Login response" << endl;
    //fade out when success
    if(!resp.getStatus()){
        ui->messageLabel->setText("Login failed");
        return;
    }
    sessionID = resp.getSessionID();
    ml->setSessionID(sessionID);

    ChatRoomPanel *crp = new ChatRoomPanel();
    crp->show();
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::setNetwork(messageListener *ml, networkQueue *nq){
    this->ml = ml;
    this->nq = nq;
}
