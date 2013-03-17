#ifndef CHATROOM_H
#define CHATROOM_H

#include <QDialog>
#include <QMouseEvent>
#include <QTextEdit>

#include "fadeinout.h"
#include "shakewindow.h"

#include "protocol/protocol.h"

namespace Ui {
    class chatRoom;
}

class chatRoom : public QDialog
{
    Q_OBJECT

public:
    explicit chatRoom(int friendid,QWidget *parent = 0);
    ~chatRoom();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

    int currentFriendID;
    void raiseChatDialog();
    int timeStamp;
signals:
    void closeDialog(int);
public slots:
    void AddMessageToList(QString mcontent,QString authorName,bool isSelf);
private slots:

    void on_SendButton_clicked();

    void on_CloseWinBtn_clicked();

    void on_shakeBtn_clicked();

    //接收到回应

    void receiveMessageResponse(Response resp);
    void on_viewFriendBtn_clicked();

private:
    Ui::chatRoom *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;
    shakeWindow shakeEffect;

    QString messageList;

    QString sendText;
    QString receiveText;



};

#endif // CHATROOM_H
