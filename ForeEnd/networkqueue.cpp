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

void networkQueue::pushEvent(Request &req){
    eventQueue.push_back(req);
    cond.wakeAll();
}

void networkQueue::run(){
    while(1){
        lock.lock();
        cond.wait(&lock);
        while(!eventQueue.isEmpty()){
            Response resp;
            Request req = eventQueue.front();
            sendRequest(req, resp);
            eventQueue.pop_front();
            dispatch(req, resp);
        }
        lock.unlock();
    }
}

void networkQueue::dispatch(Request &req, Response &resp){
    std::string type, method;

    req.getType(type);
    req.getMethod(method);

    if(type == std::string("regluar") && method == std::string("login")){
        emit loginBack(resp);
    }
}

void networkQueue::sendRequest(Request &req, Response &resp){
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
    resp.setRawData(rawData);
}


