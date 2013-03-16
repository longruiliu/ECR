#include <protocol.h>
#include <string>

int addGroupMember(int userID, int groupID, std::string msg) {
    Request req;
    req.setType("group");
    req.setMethod("joinreq");
    req.addParams(userID);
    req.addParams(groupID);
    req.addParams(msg);
}

int delGroupMember(int userID, int groupID) {
    Request req;
    req.setType("group");
    req.setMethod("quitreq");
    req.addParams(userID);
    req.addParams(groupID);
}

int getUserList(int groupID) {
    Request req;
    req.setType("group");
    req.setMethod("userlist");
    req.addParams(groupID);
}

int sendRedMsg(int groupID, std::string msg) {
    Request req;
    req.setType("group");
    req.setMethod("redmsg");
    req.addParams(groupID);
    req.addParams(msg);
}

int fetchGroupMsg(int groupID, time_t timestamp) {
    Request req;
    req.setType("group");
    req.setMethod("fetchmsg");
    req.addParams(groupID);
    req.addParams((int)timestamp);
}

int fetchGroup() {
    Request req;
    req.setType("group");
    req.setMethod("fetchgrp");
}

int addUser(std::string userName, std::string pw, std::string userInfo) {
    Request req;
    req.setType("regular");
    req.setMethod("add");
    req.addParams(userName);
    req.addParams(pw);
    req.addParams(userInfo);
}

int modifyUser(int userID, std::string newName, std::string newpw,
               int prior, std::string userInfo) {
    Request req;
    req.setType("regular");
    req.setMethod("modify");
    req.addParams(userID);
    req.addParams(newName);
    req.addParams(newpw);
    req.addParams(prior);
    req.addParams(userInfo);
}

int delUser(int userID) {
    Request req;
    req.setType("regular");
    req.setMethod("del");
    req.addParams(userID);
}

int fetchMsg() {
    Request req;
    req.setType("regular");
    req.setMethod("fetchmsg");
}

int keepAlive() {
    Request req;
    req.setType("regular");
    req.setMethod("keepalive");
}



    
