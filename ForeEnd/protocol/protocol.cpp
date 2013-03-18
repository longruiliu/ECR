/*
  Protocol layer module
*/

#include <json/json.h>
#include <map>
#include <string>
#include <stdio.h>
#include "protocol.h"

static int jsonToString(Json::Value &, std::string &);
static int stringToJson(std::string &, Json::Value &);


static std::string intToString(int);
static int stringToInt(std::string);

static int jsonToString(Json::Value &root, std::string &ret) {
    Json::FastWriter writer;
    ret = writer.write(root);
    return 0;
}

static int stringToJson(std::string &str, Json::Value &root) {
    Json::Reader reader;
    if (!reader.parse(str, root))
        return ERROR;
    return 0;
}


static int stringToInt(std::string s) {
    int ret;
    sscanf(s.c_str(), "%d", &ret);
    return ret;
}

static std::string intToString(int val) {
    char s[20];
    sprintf(s, "%d", val);
    std::string ret(s);
    return ret;
}


int Request::setSessionID(int val) {
    root["sessionID"] = val;
    return 0;
}

int Request::setType(std::string &type) {
    root["type"] = type;
    return 0;
}

int Request::setMethod(std::string &method) {
    root["method"] = method;
    return 0;
}

int Request::addParams(int val) {
    Json::Value param;
    param["type"] = "Int";
    param["value"] = val;
    root["params"].append(param);
    return 0;
}

int Request::addParams(std::string &s) {
    Json::Value param;
    param["type"] = "String";
    param["value"] = s;
    root["params"].append(param);
    return 0;
}


int Request::addParams(UserList &ul) {
    Json::Value param;
    param["type"] = "UserList";
    Json::Value arr;
    for (int i = 0; i != sizeof(ul); i++)
        arr.append(ul[i]);
    param["value"] = arr;
    root["params"].append(param);
    return 0;
}

int Request::addParams(MsgList &ml) {
    Json::Value param;
    Json::Value arr;
    Json::Value msg;
    param["type"] = "MsgList";
    for (int i = 0; i != ml.size(); i++) {
        msg["srcID"] = ml[i].srcID;
        msg["targetID"] = ml[i].targetID;
        msg["msgText"] = ml[i].msgText;
        msg["postTime"] = (int)ml[i].postTime;
        msg["msgType"] = ml[i].msgType;
        arr.append(msg);
    }
    param["value"] = arr;
    root["params"].append(param);
    return 0;
}

int Request::encode(std::string &rawString) {
    return jsonToString(root, rawString);
}

Response::Response() {
    root["status"] = ERROR;
}

Response::Response(std::string s) {
    stringToJson(s, root);
}

int Response::getStatus() const {
    return root["status"].asInt();
}

int Response::getUserInfo(UserInfo &ui) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        ui = json["userInfo"].asString();
    } catch (...)  {
        return ERROR;
    }
    return 0;
}

int Response::getUserName(std::string &ret) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        ret = json["userName"].asString();
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getUserID() const {
    try {
        Json::Value json = root["result"][0U]["value"];
        return json.asInt();
    } catch (...) {
        return ERROR;
    }
    return ERROR;
}

int Response::getGroupList(std::vector < std::pair <int, std::string> > &gpl) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i != json.size(); i++) {
            gpl.push_back(make_pair(json[i][0U].asInt(), json[i][1U].asString()));
        }
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getMsgList(std:: vector <msgRecord> &vmr) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i != json.size(); i++) {
            Json::Value temp = json[i];
            int srcID, targetID, postTime, msgType;
            std::string msgText;
            for (__typeof(temp.begin()) it = temp.begin(); it != temp.end(); it++) {
                if (it.key().asString() == "srcID")
                    srcID = (*it).asInt();
                else if (it.key().asString() == "targetID")
                    targetID = (*it).asInt();
                else if (it.key().asString() == "msgText")
                    msgText = (*it).asString();
                else if (it.key().asString() == "postTime")
                    postTime = (*it).asInt();
                else if (it.key().asString() == "msgType")
                    msgType = (*it).asInt();
            }
            MsgRecord mr(srcID, targetID, msgText, msgType);
            mr.postTime = postTime;
            vmr.push_back(mr);
        }
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getStatus(std::string &s) const {
    Json::Value root;
    stringToJson(s, root);
    return root["status"].asInt();
}

int Response::getUserInfo(std::string &s, std::string &userinfo) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        userinfo = json["userInfo"].asString();
    } catch (...)  {
        return ERROR;
    }
    return 0;
}

int Response::getUserName(std::string &s, std::string &ret) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        ret = json["userName"].asString();
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getUserID(std::string &s) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        return json.asInt();
    } catch (...) {
        return ERROR;
    }
    return ERROR;
}

int Response::getGroupList(std::string &s, std::vector < std::pair <int, std::string> > &gpl) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i != json.size(); i++) {
            gpl.push_back(make_pair(json[i][0U].asInt(), json[i][1U].asString()));
        }
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getMsgList(std::string &s, std:: vector <msgRecord> &vmr) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i != json.size(); i++) {
            Json::Value temp = json[i];
            int srcID, targetID, postTime, msgType;
            std::string msgText;
            for (__typeof(temp.begin()) it = temp.begin(); it != temp.end(); it++) {
                if (it.key().asString() == "srcID")
                    srcID = (*it).asInt();
                else if (it.key().asString() == "targetID")
                    targetID = (*it).asInt();
                else if (it.key().asString() == "msgText")
                    msgText = (*it).asString();
                else if (it.key().asString() == "postTime")
                    postTime = (*it).asInt();
                else if (it.key().asString() == "msgType")
                    msgType = (*it).asInt();
            }
            MsgRecord mr(srcID, targetID, msgText, msgType);
            mr.postTime = postTime;
            vmr.push_back(mr);
        }
    } catch (...) {
        return ERROR;
    }
    return 0;
}

std::string Response::getResType() const {
    try{
        return root["result"][0U]["type"].asString();
    } catch (...) {
        ;
     }
    return "";
}

std::string Response::getResType(std::string &s) const {
    Json::Value root;
    try{
        stringToJson(s, root);
        return root["result"][0U]["type"].asString();
    } catch (...) {
        ;
     }
    return "";
}
           
int Response::getSessionID(std::string &s) const {
    Json::Value root;
    try{
        stringToJson(s, root);
        return root["result"][0U]["value"].asInt();
    } catch (...) {
        ;
     }
    return ERROR;
}

int Response::getSessionID() const {
    try{
        return root["result"][0U]["value"].asInt();
    } catch (...) {
        ;
     }
    return ERROR;
}

Response::Response(const Response &o) {
    root = o.root;
}

int Response::getUserList(UserList &ul) const{
    try {
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i < json.size(); i++)
            ul.push_back(json[i].asInt());
    } catch (...) {
        return ERROR;
    }
    return 0;
}

int Response::getUserList(std::string &s, UserList &ul) const {
    Json::Value root;
    try {
        stringToJson(s, root);
        Json::Value json = root["result"][0U]["value"];
        for (int i = 0; i < json.size(); i++)
            ul.push_back(json[i].asInt());
    } catch (...) {
        return ERROR;
    }
    return 0;
}
