#ifndef VIEWFRIENDINFO_H
#define VIEWFRIENDINFO_H

#include <QDialog>
#include <QMouseEvent>
#include <QTextEdit>

#include "fadeinout.h"

namespace Ui {
class ViewFriendInfo;
}

class ViewFriendInfo : public QDialog
{
    Q_OBJECT
    
public:
    explicit ViewFriendInfo(QString nickName="",QString userInfo="",QWidget *parent = 0);
    ~ViewFriendInfo();
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent (QMouseEvent *);
    
private slots:
    void on_CloseWinBtn_clicked();

private:
    Ui::ViewFriendInfo *ui;

    QPoint windowPos;
    QPoint dPos;
    QPoint mousePos;

    FadeInOut fadeEffect;
};

#endif // VIEWFRIENDINFO_H
