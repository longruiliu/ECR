#include "networkqueue.h"
#include "network1.h"

networkQueue::networkQueue(QThread *parent) :
    QThread(parent)
{
}

void networkQueue::setRemote(QString &addr, QString &port){
    this->addr = addr;
    this->port = port;
}

void networkQueue::pushEvent(Nevent &req){
    eventQueue.push_back(req);
    cond.wakeAll();
}

void networkQueue::run(){
    std::string respStr;
    while(1){
        lock.lock();
        cond.wait(&lock);
        while(!eventQueue.isEmpty()){

            Nevent ev = eventQueue.front();
            sendRequest(ev.req, respStr);
            Response resp(respStr);
            eventQueue.pop_front();
            QObject::connect(this, SIGNAL(youHaveResponse(Response)), ev.callee, ev.signal);
            emit youHaveResponse(resp);
            QObject::connect(this, SIGNAL(youHaveResponse(Response)), ev.callee, ev.signal);
        }
        lock.unlock();
    }
}


void networkQueue::sendRequest(Request &req, std::string &resp){
    std::string rawData;
    Network net;

    req.encode(rawData);
    net.addData(rawData);
    if(net.connectToRemote(addr, port.toInt()) == false){
        return;
    }

    if(net.waitForDataReady() == false){
        return;
    }
    net.readData(rawData);

    resp = rawData;
}


