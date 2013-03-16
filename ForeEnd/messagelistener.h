#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

#include <QThread>
#include <QUdpSocket>
#include <QStringList>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include "protocol/protocol.h"
#include "protocol_const.h"

class messageListener : public QThread
{
    Q_OBJECT
public:
    explicit messageListener(QObject *parent = 0);


signals:
    void youHaveGroupMessage(int groupID);
    void youHaveMessage();

protected:
    void run();
public slots:
private slots:
    void handleMessage();
private:
    QUdpSocket serv;

    QMutex lock;
    QWaitCondition cond;
};

extern messageListener ml;
#endif // MESSAGELISTENER_H
