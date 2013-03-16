#include "messagelistener.h"
#include "protocol/protocol.h"
#include <string>
#include "network1.h"
#include "messagelistener.h"

messageListener::messageListener(QObject *parent) :
    QThread(parent)
{

    QObject::connect(&serv, SIGNAL(readyRead()), this, SLOT(handleMessage()));
    serv.bind(0x1024);
}

void messageListener::handleMessage(){
    char *pushMsg;
    int msgLen, msgType1, msgType2;

    msgLen = serv.pendingDatagramSize();
    pushMsg = new char[msgLen];
    msgLen = serv.readDatagram(pushMsg, msgLen);
    qDebug() << msgLen << endl;
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
    exec();
}
