#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

#include <QThread>
#include <QUdpSocket>
#include <QStringList>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include "protocol/protocol.h"

class messageListener : public QThread
{
    Q_OBJECT
public:
    explicit messageListener(QObject *parent = 0);
    messageListener(QString &userID, QString &passwd, int sessionID);
    void setRemote(QString &addr, QString &port);
    void setSessionID(int sessionID);
    bool sendRequest(Request &req, std::string &resp);
    void handleMessage();

signals:
    void youHaveMessage(Response resp);

protected:
    void run();
public slots:
private slots:
    void messageReady();
    void bind();

private:
    QUdpSocket serv;
    QString addr, port;
    int sessionID;
    int timeStamp;

    QMutex lock;
    QWaitCondition cond;
};

#endif // MESSAGELISTENER_H
