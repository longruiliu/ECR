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

 //   fadeEffect.startFadeInOut(FADEIN);

    getServerInfo();
    ui->serverIPText->setText(serverIP);
    ui->serverPortText->setText(serverPort);
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

void LoginConfig::StartFadeIn()
{
    fadeEffect.startFadeInOut(FADEIN);
}

void LoginConfig::on_okBtn_clicked()
{
    serverIP = ui->serverIPText->text();
    serverPort = ui->serverPortText->text();

    qDebug()<<serverIP<<"\n"<<serverPort<<"\n";
    saveServerInfo();

    fadeEffect.startFadeInOut(FADEOUT_EXIT);
    loginDialog *ld = new loginDialog();
    ld->show();
}

void LoginConfig::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}


void LoginConfig::getServerInfo()
{
    QString tmp;
    QFile file("config.ini");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
    }
    if(!file.atEnd())
        serverIP=file.readLine();
    serverIP.truncate(serverIP.size()-1);
    if(!file.atEnd())
        serverPort=file.readLine();
    file.close();
}

void LoginConfig::saveServerInfo()
{
    QFile file("config.ini");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug()<<"Can't open the file!"<<endl;
    }
    file.write(serverIP.toAscii());
    file.write("\n");
    file.write(serverPort.toAscii());
}
