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

const int timerRate=30;
const double changeValue=0.05;


class FadeInOut:public QObject
{
    Q_OBJECT

public:
    FadeInOut(QDialog *dia,QObject *parent = 0);
    void startFadeInOut(int effectType);

    void raiseDialog();//Show Dialog Without FadeIn FadeOut Effect

private:
    //
    QTimer *timerOpacity;
    double opalevel;
    QGraphicsOpacityEffect *opacityEffect;
    int effectType;
    QDialog *dia;

    bool isWorking;//

private slots:
    void changeOpacity();
};

#endif // FADEINOUT_H
