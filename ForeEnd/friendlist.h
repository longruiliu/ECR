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

private:
    Ui::FriendList *ui;

private slots:
    void startChatWithSelectedFriend() ;
    void onRightClick(QPoint pos);
    void refreshFriendList();
    void viewFriendInfo();
};

#endif // FRIENDLIST_H
