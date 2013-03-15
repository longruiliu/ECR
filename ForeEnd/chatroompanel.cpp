#include "chatroompanel.h"
#include "ui_chatroompanel.h"
#include "protocol/protocol.h"
#include "networkqueue.h"

extern networkQueue nq;
extern messageListener ml;

ChatRoomPanel::ChatRoomPanel(QString userID, QString passwd, int sessionID):
    ui(new Ui::ChatRoomPanel),fadeEffect(this)
{
    ui->setupUi(this);
    //add the friendlist and grouplist widget to the tabWidget
    ui->tabWidget->addTab(&friendlistWidget,QIcon(":/header/1.png"),tr("好友列表"));
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

    //get User list and group list
    getUserList();
    getGroupList();
}

ChatRoomPanel::ChatRoomPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatRoomPanel),
    fadeEffect(this)
{
    ui->setupUi(this);

    //add the friendlist and grouplist widget to the tabWidget
    ui->tabWidget->addTab(&friendlistWidget,QIcon(":/header/1.png"),tr("好友列表"));
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


void ChatRoomPanel::getUserList(){
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0, "regular");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "userlist");
    ev.req.setMethod(str);
    ev.req.setSessionID(sessionID);
    ev.callee = this;
    strcpy(ev.signal, SLOT(getUserListResponse(Response)));

    nq.pushEvent(ev);

}

void ChatRoomPanel::getGroupList(){
    Nevent ev;
    std::string str;

    ev.req.setSessionID(sessionID);

    str.clear();
    str.insert(0, "group");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "fetchgrp");
    ev.req.setMethod(str);
    ev.callee = this;
    strcpy(ev.signal, SLOT(getGroupListResponse(Response)));

    nq.pushEvent(ev);
}

void ChatRoomPanel::getUserListResponse(Response resp){
    std::vector<int>::iterator iter;
    UserList ul;
    resp.getUserList(ul);
    std::string str;

    for(iter = ul.begin(); iter != ul.end(); iter++){
        userIDList.push_back(*iter);
        userInfoRequestQueue.push_back(*iter);
        Nevent ev;

        ev.req.setSessionID(sessionID);

        str.clear();
        str.insert(0,"regular");
        ev.req.setType(str);

        str.clear();
        str.insert(0,"userinfo");
        ev.req.setMethod(str);

        ev.req.addParams(*iter);

        ev.callee = this;
        strcpy(ev.signal, SLOT(receiveUserInfoResponse(Response)));

        nq.pushEvent(ev);
    }

}

void ChatRoomPanel::getGroupListResponse(Response resp){
    qDebug() << "get Group List response" << endl;
    std::vector<std::pair<int, std::string> > gl;
    std::vector<std::pair<int, std::string> >::iterator iter;

    resp.getGroupList(gl);

    for(iter = gl.begin(); iter != gl.end(); iter++)
    {
        grouplistWidget.addGroupToList(iter->first,QString(iter->second.c_str()));
    }
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
    trayIcon->setToolTip(tr("God Talk"));
    minimizeAction = new QAction(tr("Minimize (&I)"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(hide()));
    restoreAction = new QAction(tr("Restore (&R)"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction(tr("Exit (&Q)"), this);
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
    QString titlec=tr("God Talk");
    QString textc=tr("Give you different experience");
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


void ChatRoomPanel::on_MiniButton_clicked()
{
   fadeEffect.startFadeInOut(FADEOUT_HIDE);
}

void ChatRoomPanel::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT_ALL);
}

void ChatRoomPanel::on_headerImage_clicked()
{
    //Change Personal's details
}


void ChatRoomPanel::receiveUserInfoResponse(Response resp)
{
    int id;

    id = userInfoRequestQueue.front();
    userInfoRequestQueue.pop_front();
    UserInfo _ui;
    std::string name;
    resp.getUserInfo(_ui);
    resp.getUserName(name);

    friendlistWidget.addFriendToList(id, QString(name.c_str()), QString(_ui.c_str()));

}
