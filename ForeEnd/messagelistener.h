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
    void handleMessage();

    void messageReady();

signals:
    void youHaveGroupMessage(int groupID);
    void youHaveMessage();

protected:
    void run();
public slots:
private slots:
    void bind();

private:
    QUdpSocket serv;
    QString addr, port;
    int sessionID;
    int timeStamp;

    QMutex lock;
    QWaitCondition cond;
};

extern messageListener ml;
#endif // MESSAGELISTENER_H
