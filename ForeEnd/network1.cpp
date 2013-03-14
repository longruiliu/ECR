#include <string.h>
#include "network1.h"

Network::Network(QObject *parent) :
    QObject(parent)
{
}

bool Network::send(){
    if(!socket.isValid())
        return false;

    socket.write(outdata);
    return true;
}

void Network::addData(std::string &rawData){
    outdata.clear();
    outdata.insert(0, rawData.c_str(), rawData.size());
}

void Network::readData(std::string &rawData){
    rawData.clear();
    rawData.insert(0, indata.data(), indata.size());
}

bool Network::connectToRemote(QString &addr, int port){
    socket.connectToHost(addr, port);
    if(socket.waitForConnected()){
        return true;
    }
    return false;
}

bool Network::waitForDataReady(int ms){
    if(socket.waitForReadyRead(ms) == false)
        return false;

    indata = socket.readAll();
    return true;
}
