#ifndef FRIENDLIST_H
#define FRIENDLIST_H

#include "chatroom.h"

#include <QWidget>

namespace Ui {
    class FriendList;
}

class FriendList : public QWidget
{
    Q_OBJECT

public:
    explicit FriendList(QWidget *parent = 0);
    ~FriendList();

    void addFriendToList(int friendID, QString nickName, QString friendInfo);
    static QString& getNickname(int userID);
private:
    Ui::FriendList *ui;

    QVector<int> friendIDList;//维护了好友ID的列表
    static QMap<int, QString> friendInfoList;
    static QMap<int, QString> nickNameList;
    QMap<int,chatRoom*> chatRoomMap;//维护了好友聊天对话框的列表

private slots:
    void startChatWithSelectedFriend(int firendID=0) ;
    void onRightClick(QPoint pos);
    void refreshFriendList();
    void viewFriendInfo();
    void handleChatRoomClose(int friendID);

 //   void getMessageArrive();

    void receiveResponse(Response resp);
};

#endif // FRIENDLIST_H
