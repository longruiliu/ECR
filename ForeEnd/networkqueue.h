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

class Nevent{
public:
    QObject *callee;
    char signal[48];
    Request req;
};

class networkQueue : public QThread
{
    Q_OBJECT
public:
    explicit networkQueue(QThread *parent = 0);
    void setRemote(QString &addr, QString &port);
    void pushEvent(Nevent &req);
protected:
    void run();
private:
    void sendRequest(Request &req,std::string &resp);

    QTcpSocket socket;
    QString addr,port;
    QQueue<Nevent> eventQueue;
    QMutex lock;
    QWaitCondition cond;
signals:
    void youHaveResponse(Response resp);
public slots:

};

#endif // NETWORKQUEUE_H
