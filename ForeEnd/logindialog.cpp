#include "logindialog.h"
#include "ui_logindialog.h"
#include "protocol/protocol.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);

    conf = new LoginConfig(this);

    QObject::connect(nq, SIGNAL(loginBack(Response)), this, SLOT(receiveLoginResponse(Response)));
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
    conf->show();
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::on_LoginBtn_clicked()
{

    Request req;
    //Here we have IP and port so we can
    //start network queue thread.
    nq->setRemote(conf->serverIP, conf->serverPort);
    nq->start();

    //Don't start messageListener thread cause we
    //do not login successfully and we konw nothing
    //about sessionID. Here we just set server IP and port
    //for network connections.
     ml->setRemote(conf->serverIP, conf->serverPort);

     std::string str;
    //send login request
    req.setSessionID(0);
    str.insert(0, "regular");
    req.setType(str);

    str.clear();
    str.insert(0,"login");
    req.setMethod(str);

    str.clear();
    str.insert(0, userName.toLocal8Bit().data());
    req.addParams(str);

    str.clear();
    str.insert(0, userPassword.toLocal8Bit().data());
    req.addParams(str);
    nq->pushEvent(req);

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

void loginDialog::receiveLoginResponse(Response resp)
{

    //fade out when success
    if(!resp.getStatus()){
        ui->messageLabel->setText("登陆失败");
        return;
    }
    sessionID = resp.getSessionID();
    ml->setRemote(userName, userPassword);
    ml->setSessionID(sessionID);
    ml->start();

    ChatRoomPanel *crp = new ChatRoomPanel();
    crp->show();
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void loginDialog::setNetwork(messageListener *ml, networkQueue *nq){
    this->ml = ml;
    this->nq = nq;
}
