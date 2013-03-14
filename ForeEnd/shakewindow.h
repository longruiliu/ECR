#ifndef SHAKEWINDOW_H
#define SHAKEWINDOW_H

#include <QtGui>
#include <QObject>
#include <QTimer>

enum {MaxLimitTimes = 20};
enum {MaxLimitSpace = 8};
enum {ShakeSpeed = 30};


class shakeWindow : public QObject
{
    Q_OBJECT

public:
    shakeWindow(QDialog *dia,QObject *parent = 0);
    void startShake();

private:
    QDialog *dia;
    QTimer* m_timer;
    int m_nPosition;
    QPoint m_curPos;


private slots:
    void slot_timerOut();
};

#endif // SHAKEWINDOW_H
