#include "shakewindow.h"

shakeWindow::shakeWindow(QDialog *dia,QObject *parent):QObject(parent)
{
    this->dia=dia;
    m_timer=new QTimer(this);
    QObject::connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_timerOut()));
    m_nPosition=MaxLimitTimes;
}

void shakeWindow::startShake()
{
    if(m_nPosition < MaxLimitTimes)
        return;
    m_nPosition=1;
    m_curPos=this->dia->pos();
    m_timer->start(ShakeSpeed);
}

void shakeWindow::slot_timerOut()
{
    if(m_nPosition < MaxLimitTimes)
    {
        ++m_nPosition;
        switch(m_nPosition%4)
        {
        case 1:
        {
            QPoint tmpPos(m_curPos.x(),m_curPos.y()-MaxLimitSpace);
            this->dia->move(tmpPos);
        }
        break;
        case 2:
        {
            QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y()-MaxLimitSpace);
            this->dia->move(tmpPos);
        }
        break;
        case 3:
        {
            QPoint tmpPos(m_curPos.x()-MaxLimitSpace,m_curPos.y());
            this->dia->move(tmpPos);
        }
        break;
        default:
        case 0:
            this->dia->move(m_curPos);
            break;
        }
    }
    else
    {
        m_timer->stop();
    }
}
