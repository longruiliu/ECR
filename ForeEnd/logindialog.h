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

    //窗口拖动鼠标移动有关
    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //和窗口的淡入淡出有关
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
