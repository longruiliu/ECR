#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTimer>

#include "loginconfig.h"
#include "chatroompanel.h"

#include "fadeinout.h"
#include "registerdialog.h"


namespace Ui {
    class loginDialog;
}

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

    //�����϶�����ƶ��й�
    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //�ʹ��ڵĵ��뵭���й�
    FadeInOut fadeEffect;

    QString userName;
    QString userPassword;

private slots:
    void on_configBtn_clicked();
    void on_LoginBtn_clicked();
    void on_CloseWinBtn_clicked();
    void on_registerBtn_clicked();
};

#endif // LOGINDIALOG_H
