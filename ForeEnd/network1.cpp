#include <string.h>
#include "network1.h"
#include <windows.h>
#include <winsock2.h>

//#pragma comment(lib, "ws2_32.lib")

Network::Network(QObject *parent) :
    QObject(parent)
{
}

bool Network::send(){
    if(!socket.isValid())
        return false;

    socket.write(outdata);
    socket.waitForBytesWritten();
    shutdown((SOCKET)socket.socketDescriptor(), SD_SEND);
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
    if(socket.waitForDisconnected(ms) == false)
    {
        qDebug()<<"No Data Arrive in time";
        return false;
    }
    while(socket.bytesAvailable())
        indata += socket.readAll();
    return true;
}
