﻿#ifndef GROUPCHATDIALOG_H
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

private slots:
    void on_CloseWinBtn_clicked();
    void startChatWithSelectedFriend() ;

    void on_SendMessageBtn_clicked();

    void receiveResponse(Response resp);

private:
    Ui::GroupChatDialog *ui;

    int currentGroupID;


    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;

    QString sendText;
    QString receiveText;
};

#endif // GROUPCHATDIALOG_H
