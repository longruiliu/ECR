#include "chatroompanel.h"
#include "ui_chatroompanel.h"
#include "protocol/protocol.h"
#include "networkqueue.h"
#include "friendlist.h"
#include "userinfoconfig.h"


extern networkQueue nq;
extern messageListener ml;

ChatRoomPanel::ChatRoomPanel(QString userID, QString passwd, int sessionID):
    ui(new Ui::ChatRoomPanel),fadeEffect(this)
{
    ui->setupUi(this);
    //add the friendlist and grouplist widget to the tabWidget
    ui->tabWidget->addTab(&friendlistWidget,QIcon(":/header/1on.png"),tr("好友列表"));
    ui->tabWidget->addTab(&grouplistWidget,QIcon(":/header/2.png"),tr("群组列表"));

    //system tray
    createTrayIcon();
    startTray();

    //window's style
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->move(900,100);

    //fade in fade out
    fadeEffect.startFadeInOut(FADEIN);

    this->userID = userID;
    this->passwd = passwd;
    this->sessionID = sessionID;

    //更新个人信息

    connect(&friendlistWidget,SIGNAL(getMyInfo(QString,QString)),
            this,SLOT(UpdateMyInfo(QString,QString)));
}

ChatRoomPanel::ChatRoomPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatRoomPanel),
    fadeEffect(this)
{
    ui->setupUi(this);

    //add the friendlist and grouplist widget to the tabWidget
    ui->tabWidget->addTab(&friendlistWidget,QIcon(":/header/1on.png"),tr("好友列表"));
    ui->tabWidget->addTab(&grouplistWidget,QIcon(":/header/2.png"),tr("群组列表"));

    //system tray
    createTrayIcon();
    startTray();

    //window's style
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    this->move(900,100);

    //fade in fade out
    fadeEffect.startFadeInOut(FADEIN);
}

void ChatRoomPanel::UpdateMyInfo(QString myNickName, QString myInfo)
{
    ui->nameLineEdit->setText(myNickName);
    ui->userInfoText->setText(myInfo);
    userNickName=myNickName;
    userInfo=myInfo;
}




ChatRoomPanel::~ChatRoomPanel()
{
    delete ui;
}


void ChatRoomPanel::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}

void ChatRoomPanel::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}


void ChatRoomPanel::createTrayIcon()
{
    QIcon icon = QIcon(":/header/logo.png");
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip(tr("子曰USay"));
    minimizeAction = new QAction(tr("最小化 (&I)"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    restoreAction = new QAction(tr("还原 (&R)"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction(tr("退出 (&Q)"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);
    trayIcon->setContextMenu(trayIconMenu);
}

void ChatRoomPanel::startTray()
{
    trayIcon->show();
    QString titlec=tr("子曰USay");
    QString textc=tr("给你神一般的聊天体验");
    trayIcon->showMessage(titlec,textc,QSystemTrayIcon::Information,5000);

    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,
            SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
}

void ChatRoomPanel::trayiconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        this->showNormal();
        this->raise();
        fadeEffect.startFadeInOut(FADEIN);
        break;
    default:
        break;
    }
}


void ChatRoomPanel::sendLogOutToServer()
{
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0,"regular");
    ev.req.setType(str);

    str.clear();
    str.insert(0,"logout");
    ev.req.setMethod(str);

    ev.callee = this;
    strcpy(ev.signal, SLOT(NULL));

    nq.pushEvent(ev);
}

void ChatRoomPanel::on_MiniButton_clicked()
{
   fadeEffect.startFadeInOut(FADEOUT_HIDE);
}

void ChatRoomPanel::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT_ALL);
    sendLogOutToServer();
}

void ChatRoomPanel::on_headerImage_clicked()
{
    //Change Personal's details
    UserInfoConfig *uic = new UserInfoConfig(userID,userNickName,userInfo);
    uic->show();
}

void ChatRoomPanel::on_pushButton_clicked()
{
    if(!QDesktopServices::openUrl(QUrl::fromLocalFile("help.doc")))
    {
        QMessageBox::about( this , tr("子曰USay") , tr("打开帮助文档失败！") ) ;
    }
}
