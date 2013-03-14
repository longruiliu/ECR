#ifndef MESSAGELISTENER_H
#define MESSAGELISTENER_H

#include <QThread>
#include <QUdpSocket>
#include <QStringList>
#include <QString>
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
signals:
    void youHaveMessage(Response resp);

protected:
    void run();
public slots:
private slots:
    void messageReady();

private:
    QUdpSocket serv;
    QString addr, port;
    int sessionID;
    int timeStamp;
};

#endif // MESSAGELISTENER_H
