#include "chatroompanel.h"
#include "ui_chatroompanel.h"

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
    this->sessoinID = sessionID;
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


void ChatRoomPanel::receiveResponse(Response resp)
{

}
