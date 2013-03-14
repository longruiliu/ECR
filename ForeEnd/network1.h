#ifndef NETWORK_H
#define NETWORK_H

#include <QThread>
#include <QByteArray>
#include <QTcpSocket>
#include <string>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = 0);
    void addData(std::string &rawData);
    void readData(std::string &rawData);
    bool connectToRemote(QString &addr, int port);
    bool waitForDataReady(int ms = 3000);
    bool send();
signals:
public slots:

private:
    QTcpSocket socket;
    QByteArray indata, outdata;
};

#endif // NETWORK_H
