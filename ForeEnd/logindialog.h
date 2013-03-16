#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTimer>

#include "loginconfig.h"
#include "chatroompanel.h"

#include "fadeinout.h"
#include "registerdialog.h"

#include "messagelistener.h"
#include "networkqueue.h"


extern int myUserID;

namespace Ui {
    class loginDialog;
}
class LoginConfig;
class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = 0);
    ~loginDialog();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

private:


    Ui::loginDialog *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;

    QString userName;
    QString userPassword;
    int sessionID;

    //loginConfig to get server IP and port
    LoginConfig *conf;

private slots:
    void on_configBtn_clicked();
    void on_LoginBtn_clicked();
    void on_CloseWinBtn_clicked();
    void on_registerBtn_clicked();

    void receiveLoginResponse(Response resp);
};

#endif // LOGINDIALOG_H
