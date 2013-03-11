#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include "logindialog.h"
#include "fadeinout.h"

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

private:
    Ui::RegisterDialog *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //和窗口淡入淡出有关的变量
    FadeInOut fadeEffect;

    QString userName;
    QString userPassword1;
    QString userPassword2;
    QString userNickName;

private slots:
    void on_OkBtn_clicked();
    void on_CloseWinBtn_clicked();
};

#endif // REGISTERDIALOG_H


