#ifndef LOGINCONFIG_H
#define LOGINCONFIG_H

#include <QDialog>
#include <QMouseEvent>
#include "logindialog.h"
#include "fadeinout.h"
#include <QFile>

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

    void getServerInfo();
    void saveServerInfo();
    QString serverIP;
    QString serverPort;

private:
    Ui::LoginConfig *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    //窗口淡入淡出效果
    FadeInOut fadeEffect;

private slots:
    void on_okBtn_clicked();
    void on_CloseWinBtn_clicked();
};

#endif // LOGINCONFIG_H
