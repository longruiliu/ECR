#ifndef USERINFOCONFIG_H
#define USERINFOCONFIG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTextEdit>

#include "fadeinout.h"

namespace Ui {
class UserInfoConfig;
}

class UserInfoConfig : public QDialog
{
    Q_OBJECT
    
public:
    explicit UserInfoConfig(QString userName="",QString NickName="",
                            QString userInfo="",QWidget *parent = 0);
    ~UserInfoConfig();

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);
    
private slots:
    void on_CloseWinBtn_clicked();

private:
    Ui::UserInfoConfig *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;

    QString userNickName;
    QString userInfo;
    QString newPsw1;
    QString newPsw2;
};

#endif // USERINFOCONFIG_H
