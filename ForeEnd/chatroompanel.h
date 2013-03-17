#ifndef CHATROOMPANEL_H
#define CHATROOMPANEL_H

#include <QtGui>
#include <QDialog>
#include <QVector>
#include "protocol/protocol.h"
#include "friendlist.h"
#include "grouplist.h"
#include "networkqueue.h"
#include "messagelistener.h"
#include "logindialog.h"

#include "fadeinout.h"
#include <QQueue>


namespace Ui {
    class ChatRoomPanel;
}

class ChatRoomPanel : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRoomPanel(QWidget *parent = 0);
    ChatRoomPanel(QString userID, QString passwd, int sessionID);
    ~ChatRoomPanel();

    void getUserList();
    void getGroupList();
    void getSingleUserInfo(int id);
    void getSingleGroupInfo(int id);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

    int sessionID;

    void sendLogOutToServer();

private:
    Ui::ChatRoomPanel *ui;
    //groupID list
    QVector<int> groupIDList;

    //Account information
    QString userID, passwd;

    //Personal Infoimation
    QString userNickName,userInfo;


    //Tab控件切换好友列表群列表
    FriendList friendlistWidget;
    GroupList  grouplistWidget;

    //拖动鼠标移动窗口有关
    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //系统托盘有关
    QSystemTrayIcon *trayIcon;
    void createTrayIcon();
    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;
    QMenu   *trayIconMenu;

    //窗口淡入淡出有关
    FadeInOut fadeEffect;


private slots:
    //系统托盘
    void startTray();
    void trayiconActivated(QSystemTrayIcon::ActivationReason reason);
    //最小化窗口到系统托盘
    void on_MiniButton_clicked();

    void on_CloseWinBtn_clicked();
    void on_headerImage_clicked();

    //接受FirendList发过来的自己信息
    void UpdateMyInfo(QString myNickName,QString myInfo);
};

#endif // CHATROOMPANEL_H
