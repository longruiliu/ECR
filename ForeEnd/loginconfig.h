#ifndef LOGINCONFIG_H
#define LOGINCONFIG_H

#include <QDialog>
#include <QMouseEvent>
#include "logindialog.h"
#include "fadeinout.h"

namespace Ui {
    class LoginConfig;
}

class LoginConfig : public QDialog
{
    Q_OBJECT

public:
    explicit LoginConfig(QWidget *parent = 0);
    ~LoginConfig();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);

private:
    Ui::LoginConfig *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //和窗口淡入淡出有关的变量
    FadeInOut fadeEffect;

    QString serverIP;
    QString serverPort;

private slots:
    void on_okBtn_clicked();
    void on_CloseWinBtn_clicked();
};

#endif // LOGINCONFIG_H
