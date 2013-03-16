#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog),
    fadeEffect(this)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    conf = new LoginConfig();

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
    /* This is for register */
    Nevent ev;
    std::string str;
    //send login request

    //We must get server IP and port from loginconfig
    if(conf->serverIP.isEmpty() || conf->serverPort.isEmpty()){
        qDebug() << "We must configure server IP and port first" << endl;
        return;
    }
    nq.setRemote(conf->serverIP, conf->serverPort);

    ev.req.setSessionID(0);
    str.insert(0, "regular");
    ev.req.setType(str);

    userName=ui->userNameEdit->text();
    userPassword1=ui->userPsw1Edit->text();
    userPassword2=ui->userPsw2Edit->text();
    userNickName=ui->userNickNameEdit->text();
    if(userName.size()!= 0 && userPassword1 == userPassword2 && userNickName.size() != 0 )
    {
        qDebug() << userName << userPassword1 << userNickName << endl;
        str.clear();
        str.insert(0,"register");
        ev.req.setMethod(str);

        ev.req.addParams(userName.toInt()); // userName

        str.clear();
        str.insert(0, userPassword1.toLocal8Bit().data());
        ev.req.addParams(str); // userPasswd

        str.clear();
        str.insert(0,userNickName.toLocal8Bit().data());
        ev.req.addParams(str); // userNickName

        ev.callee = (QObject *)this;
        strcpy(ev.signal, SLOT(receiveResponse(Response)));

        nq.pushEvent(ev);

        conf->close();

        fadeEffect.startFadeInOut(FADEOUT_EXIT);
        loginDialog *ld = new loginDialog();
        ld->show();

    }
    else
    {
        qDebug() << "input error" << endl;
        return;
    }
}

void RegisterDialog::receiveResponse(Response resp)
{
    qDebug()<< "recveived register respone" << endl;
    if(resp.getStatus()){
        QMessageBox msgBox;
        msgBox.setText("registed error!");
        msgBox.exec();
        return;
    }
}

