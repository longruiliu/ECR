#ifndef GROUPCHATDIALOG_H
#define GROUPCHATDIALOG_H
#include <QMouseEvent>

#include <QDialog>
#include "fadeinout.h"
#include "chatroom.h"

namespace Ui {
    class GroupChatDialog;
}

class GroupChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GroupChatDialog(int groupID,QWidget *parent = 0);
    ~GroupChatDialog();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

    void raiseChatDialog();

    void addFriendTolist(int friendid,QString nickname);

    void AddMessageToList(QString mcontent, QString authorName,time_t postTime,int senderType);

    //按Ctrol+Enter发送消息
    bool eventFilter(QObject *obj, QEvent *e);

signals:
    void closeDialog(int);

private:
    Ui::GroupChatDialog *ui;

    int currentGroupID;

    time_t lastMsgTime;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;
    shakeWindow shakeEffect;

    QString messageList;
    QString sendText;
    QString receiveText;

    QVector<int> friendIDList;//维护了好友ID的列表
    QMap<int,chatRoom*> chatRoomMap;//维护了好友聊天对话框的列表


    void getMemberList();

public slots:
    void getGroupMsg();
private slots:
    void startChatWithSelectedFriend(int firendID=0) ;
    void on_CloseWinBtn_clicked();
    void on_SendMessageBtn_clicked();
    void handleChatRoomClose(int friendID);

    void onRightClick(QPoint pos);
    void viewFriendInfo();

    void on_shakeBtn_clicked();

    void receiveGroupMsg(Response resp);

    void sendGroupMessageResponse(Response resp);
    void receiveMemberList(Response resp);

};

#endif // GROUPCHATDIALOG_H
