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
    explicit GroupChatDialog(QWidget *parent = 0);
    ~GroupChatDialog();


    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);


private slots:
    void on_CloseWinBtn_clicked();
    void startChatWithSelectedFriend() ;

    void on_SendMessageBtn_clicked();

    void receiveResponse(Response resp);

private:
    Ui::GroupChatDialog *ui;


    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;

    QString sendText;
    QString receiveText;
};

#endif // GROUPCHATDIALOG_H
