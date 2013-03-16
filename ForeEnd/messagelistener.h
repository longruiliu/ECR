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
    messageListener(QString &userID, QString &passwd, int sessionID);
    void setRemote(QString &addr, QString &port);
    void setSessionID(int sessionID);
    void handleMessage();

signals:
    void youHaveGroupMessage(int groupID);
    void youHaveMessage();

protected:
    void run();
public slots:
private slots:
    void bind();
    void messageReady();

private:
    QUdpSocket serv;
    QString addr, port;
    int sessionID;
    int timeStamp;

    QMutex lock;
    QWaitCondition cond;
};

#endif // MESSAGELISTENER_H
