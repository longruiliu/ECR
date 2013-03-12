#include "fadeinout.h"

FadeInOut::FadeInOut(QDialog *dia,QObject *parent):QObject(parent)
{
    this->dia=dia;
    opacityEffect = new QGraphicsOpacityEffect();
    dia->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(0.0);

    timerOpacity = new QTimer(this);
    QObject::connect(timerOpacity,SIGNAL(timeout()),this,SLOT(changeOpacity()));
    isWorking=false;
}

void FadeInOut::startFadeInOut(int effectType)
{
    //�������ִ��һ��������������˳�
    if(isWorking && effectType==this->effectType)
        return;
    //�����𽥵��뵭��
    this->effectType=effectType;
    opalevel=1.0;
    if(effectType==FADEIN)
    {
        opalevel=0.0;
    }
    timerOpacity->start(timerRate);
    isWorking=true;
}

void FadeInOut::changeOpacity()
{
    if(effectType==FADEIN)
    {
        if (opalevel >= 1.0)
        {
            timerOpacity->stop();
            isWorking=false;
            return;
        }
        opacityEffect->setOpacity(opalevel+=changeValue);
    }
    else
    {
        if (opalevel <= 0.0)
        {
            timerOpacity->stop();
            isWorking=false;
            if(effectType==FADEOUT_EXIT)
                dia->close();
            else if(effectType==FADEOUT_HIDE)
                dia->hide();
            else if(effectType==FADEOUT_EXIT_ALL)
                exit(1);
            return;
        }
        opacityEffect->setOpacity(opalevel-=changeValue);
    }
}