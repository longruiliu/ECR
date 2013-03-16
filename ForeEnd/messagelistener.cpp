#include "messagelistener.h"
#include "protocol/protocol.h"
#include <string>
#include "network1.h"

messageListener::messageListener(QObject *parent) :
    QThread(parent)
{
    sessionID = -1;
    timeStamp = 0;
    QObject::connect(&serv, SIGNAL(readyRead()), this, SLOT(messageReady()));
    QObject::connect(this,SIGNAL(started()), this, SLOT(bind()));
}

messageListener::messageListener(QString &addr, QString &port, int sessionID){
    this->addr = addr;
    this->port = port;
    this->sessionID = sessionID;
}

void messageListener::messageReady(){
    cond.wakeAll();
}

void messageListener::handleMessage(){
    char *pushMsg;
    int msgLen, msgType1, msgType2;

    if(addr.isEmpty() || port.isEmpty() || sessionID == -1){
        qDebug() << "You must assigned sessionID server IP and port for message listener" << endl;
        return;
    }
    if(!serv.hasPendingDatagrams())
        return;

    msgLen = serv.pendingDatagramSize();
    pushMsg = new char[msgLen];
    msgLen = serv.readDatagram(pushMsg, msgLen);

    if(msgLen < 8)
        return;

    //The bytes after first four bytes will be dropped
    msgType1 = *(int *)pushMsg;
    msgType2 = *(int *)(pushMsg+4);

    if(msgType1 == NOTIFY_GROUP_MSG){
        emit youHaveGroupMessage(msgType2);
    }else if(msgType1 == NOTIFY_P2P_MSG){
        emit youHaveMessage();
    }
}

void messageListener::run(){
    while(1){
        lock.lock();
        cond.wait(&lock);
        handleMessage();
        lock.unlock();
    }
    exec();
}

void messageListener::setRemote(QString &addr, QString &port){
    this->addr = addr;
    this->port = port;
}

void messageListener::setSessionID(int sessionID){
    this->sessionID = sessionID;
}


void messageListener::bind(){
    serv.bind(port.toInt());
}
