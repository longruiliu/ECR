#include "networkqueue.h"
#include "network1.h"
#include <QMetaType>

networkQueue::networkQueue(QThread *parent) :
    QThread(parent)
{
    qRegisterMetaType<Response>("Response");
}

void networkQueue::setRemote(QString &addr, QString &port){
    this->addr = addr;
    this->port = port;
}

void networkQueue::pushEvent(Nevent req){
    eventQueue.push_back(req);
    cond.wakeAll();
}

void networkQueue::run(){
    qDebug() << "Network Queue Ready";
    std::string respStr;
    while(1){
        lock.lock();
        cond.wait(&lock);
        qDebug() << "I am awake";
        while(!eventQueue.isEmpty()){
            if(addr.isEmpty() || port.isEmpty()){
                qDebug() << "You must assign server IP and port for network queueu" << endl;
                break;
            }
            Nevent ev = eventQueue.front();
            QObject::connect(this, SIGNAL(youHaveResponse(Response)),
                             ev.callee, ev.signal, Qt::QueuedConnection);

            sendRequest(ev.req, respStr);
            qDebug() << respStr.c_str();
            eventQueue.pop_front();

            if(respStr.empty()){
                Response resp;
                emit youHaveResponse(resp);
            }else{
                Response resp(respStr);
                emit youHaveResponse(resp);
            }
            QObject::disconnect(this, SIGNAL(youHaveResponse(Response)),
                             ev.callee, ev.signal);
        }
        lock.unlock();
    }

    exec();
}


void networkQueue::sendRequest(Request &req, std::string &resp){
    std::string rawData;
    Network net;

    req.encode(rawData);
    net.addData(rawData);
    resp.clear();
    qDebug() << rawData.c_str() << endl;
    if(net.connectToRemote(addr, port.toInt()) == false){
        qDebug() << "Can not connect to remote" << endl;
        return;
    }

    net.send();
    if(net.waitForDataReady() == false){
        qDebug() << "The server don't response" << endl;
        return;
    }
    net.readData(rawData);

    resp = rawData;
}


