#include "messagelistener.h"
#include "protocol/protocol.h"
#include <string>
#include "network1.h"

messageListener::messageListener(QObject *parent) :
    QThread(parent)
{
    serv = new QUdpSocket(this);
    timeStamp = 0;
    QObject::connect(serv, SIGNAL(readyRead()), this, SLOT(messageReady()));
}

messageListener::messageListener(QString &addr, QString &port, int sessionID){
    this->addr = addr;
    this->port = port;
    this->sessionID = sessionID;
}

void messageListener::messageReady(){
    char *pushMsg;
    int msgLen, msgType;
    Request req;
    std::string respStr;

    if(addr.isEmpty() || port.isEmpty())
        return;
    if(!serv->hasPendingDatagrams())
        return;

    msgLen = serv->pendingDatagramSize();
    pushMsg = new char[msgLen];
    msgLen = serv->readDatagram(pushMsg, msgLen);

    //The bytes after first four bytes will be dropped
    msgType = *(int *)pushMsg;

    std::string str;
    req.setSessionID(sessionID);
    switch(msgType){
    case 0:
        str.clear();
        str.insert(0,"regular");
        req.setMethod(str);

        str.clear();
        str.insert(0,"fetchmsg");
        req.setMethod(str);
        break;
    default:
        str.clear();
        str.insert(0, "group");
        req.setMethod(str);

        str.clear();
        str.insert(0, "fetchmsg");
        req.setMethod(str);
        req.addParams(msgType);
        break;
    }
    req.addParams(timeStamp);

    sendRequest(req, respStr);
    Response resp(respStr);
    emit youHaveMessage(resp);
}

void messageListener::run(){
    serv->bind(port.toInt());
}

void messageListener::setRemote(QString &addr, QString &port){
    this->addr = addr;
    this->port = port;
}

void messageListener::setSessionID(int sessionID){
    this->sessionID = sessionID;
}

bool messageListener::sendRequest(Request &req, std::string &resp){

    std::string rawData;
    Network net;
    req.encode(rawData);

    net.addData(rawData);
    if(net.connectToRemote(addr, port.toInt()) == false){
        return false;
    }

    if(net.waitForDataReady() == false){
        return false;
    }
    net.readData(rawData);

    resp = rawData;
    return true;
}

