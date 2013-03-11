#ifndef FADEINOUT_H
#define FADEINOUT_H

#include <QtGui>
#include <QObject>
#include <QTimer>
#include <QGraphicsOpacityEffect>

#define FADEIN              0
#define FADEOUT             1
#define FADEOUT_EXIT        2
#define FADEOUT_EXIT_ALL    3
#define FADEOUT_HIDE        4

const int timerRate=100;
const double changeValue=0.05;


//ʵ�ִ��ڵ��뵭��Ч������
class FadeInOut:public QObject
{
    Q_OBJECT

public:
    FadeInOut(QDialog *dia,QObject *parent = 0);
    void startFadeInOut(int effectType);

private:
    //���ڵ��뵭���й�
    QTimer *timerOpacity;
    double opalevel;
    QGraphicsOpacityEffect *opacityEffect;
    int effectType;
    QDialog *dia;

    bool isWorking;//��������ִ��һ���������

private slots:
    void changeOpacity();
};

#endif // FADEINOUT_H
