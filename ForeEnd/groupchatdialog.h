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

signals:
    void closeDialog(int);

private:
    Ui::GroupChatDialog *ui;

    int currentGroupID;


    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;

    QString sendText;
    QString receiveText;

    QVector<int> friendIDList;//维护了好友ID的列表
    QMap<int,chatRoom*> chatRoomMap;//维护了好友聊天对话框的列表

private slots:
    void startChatWithSelectedFriend(int firendID=0) ;
    void on_CloseWinBtn_clicked();
    void on_SendMessageBtn_clicked();
    void handleChatRoomClose(int friendID);
    void receiveResponse(Response resp);
};

#endif // GROUPCHATDIALOG_H
