#ifndef CHATROOMPANEL_H
#define CHATROOMPANEL_H

#include <QtGui>
#include <QDialog>
#include "friendlist.h"
#include "grouplist.h"

#include "fadeinout.h"

namespace Ui {
    class ChatRoomPanel;
}

class ChatRoomPanel : public QDialog
{
    Q_OBJECT

public:
    explicit ChatRoomPanel(QWidget *parent = 0);
    ~ChatRoomPanel();


    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

private:
    Ui::ChatRoomPanel *ui;

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
};

#endif // CHATROOMPANEL_H
