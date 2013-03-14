#ifndef NETWORKQUEUE_H
#define NETWORKQUEUE_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QString>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include "protocol/protocol.h"

class networkQueue : public QThread
{
    Q_OBJECT
public:
    explicit networkQueue(QThread *parent = 0);
    void setRemote(QString &addr, QString &port);
    void pushEvent(Request &req);
protected:
    void run();
private:
    void dispatch(Request &req,Response &resp);
    void sendRequest(Request &req,Response &resp);

    QTcpSocket socket;
    QString addr,port;
    QQueue<Request> eventQueue;
    QMutex lock;
    QWaitCondition cond;
signals:
    void loginBack(Response resp);
public slots:

};

#endif // NETWORKQUEUE_H
