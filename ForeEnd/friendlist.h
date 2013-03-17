#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include "chatroom.h"

#include <QWidget>
#include <QTimer>

namespace Ui {
    class FriendList;
}

#define FreshRate 3000

class FriendList : public QWidget
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = 0);
    ~FriendList();

    void addFriendToList(int friendID, QString nickName, QString friendInfo);
    static QString& getNickname(int userID);
    static QString& getFriendInfo(int userID);

    void pullMessageFromServer();
    void sendKeepAliveToServer();

private:
    Ui::FriendList *ui;

    QVector<int> friendIDList;//维护了好友ID的列表
    static QMap<int, QString> friendInfoList;
    static QMap<int, QString> nickNameList;
    QMap<int,chatRoom*> chatRoomMap;//维护了好友聊天对话框的列表
    QQueue<int> userInfoRequestQueue;
    QVector<int> userIDList;

    //定期拉取消息
    QTimer *timerRefresh;

signals:
    void getMyInfo(QString,QString);

public slots:
    void getUserList();
private slots:
    void startChatWithSelectedFriend(int firendID=0) ;
    void onRightClick(QPoint pos);
    void refreshFriendList();
    void viewFriendInfo();
    void handleChatRoomClose(int friendID);

    void newMessage();
    void newMessaveResponse(Response resp);

 //   void getMessageArrive();

    void receiveResponse(Response resp);
    void receiveUserInfoResponse(Response resp);
    void getUserListResponse(Response resp);
    void KeepAliveResponse(Response resp);

    //向服务器拉取消息
    void RefreshFromServer();

};

#endif // FRIENDLIST_H
