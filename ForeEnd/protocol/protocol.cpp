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

//static std::string serialUserInfo(UserInfo &);
//static std::string serialUserList(UserList &);

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

/*
class Wrapper {
public:
    std::string wrap(Request request) {
        std::string ret;
        if (jsonToString(request.root, ret))
            return ret;
        return "";
    }
    std::string getMethod(Request request) const {
        return request.root["method"];
    }
    std::string getType(Request request) const{
        return request.root["type"];
    }
};
*/

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

/*
static std::string serialUserList(UserList &ul) {
    Json::Value root;
    std::string ret;
    for (int i = 0; i != ul.size(); i++) {
        std::string tmp = intToString(ul[i]);
        root.append(tmp);
    }
    if (jsonToString(root, ret))
        return ret;
    return "";
}
*/

/*
static std::string serialUserInfo(UserInfo &ui) {
    Json::Value root;
    for (__typeof(ui.begin()) it = ui.begin(); it != ui.end(); it++)
        root[it->first] = it->second;
    std::string ret;
    if (jsonToString(root, ret))
        return ret;
    return "";
}
*/

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

int Request::addParams(UserInfo &ui) {
    Json::Value param;
    param["type"] = "UserInfo";
    Json::Value json;
    for (__typeof(ui.begin()) it = ui.begin(); it != ui.end(); it++)
        json[it->first] = ui[it->second];
    param["value"] = json;
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

/*
int sendRequest(Request &request, Response &response) {
    Wrapper wrapper;
    std::string serial, method, type;
    serial = wrapper.wrap(request);
    if (serial != "") {
        response.reqBak["method"] = wrapper.getMethod(request);
        response.reqBak["type"] = wrapper.getType(request);
        Json::Value root;
        if (stringToJson(ret, root) != ERROR) {
            if (root["status"] != ERR_OK) {
            }
        } else {
        }
    } else
        return ERR_INVALID_REQUEST;
    return 0;
}

int Response::getUserList(UserList &ul) const {
    Json::Value arr;
    if (root.isMember("userList") && root["userList"].isArray())
        arr = root["userList"];
    else
        return ERROR;
    for (int i = 0; i != arr.size(); i++)
        ul.push_back(stringToInt(arr[i].asString()));
    return 0;
}

int Response::getSessionID() const {
    if (!root.isMember("sessionID") || !root["sessionID"].isInt())
        return ERROR;
    return root["sessionID"].asInt();
}


int Response::getUserInfo(UserInfo &ui) const {
    if (!root.isMember("userInfo") || !root["userInfo"].isString())
        return ERROR;
    Json::Value json;
    std::string str = root["userInfo"].asString();
    if (stringToJson(str, json) == ERROR)
        return ERROR;
    for (__typeof(json.begin()) it = json.begin(); it != json.end(); it++) {
        if (it.key().isString() && (*it).isString())
            ui[it.key().asString()] = (*it).asString();
        else
            return ERROR;
    }
    return 0;
}


int Response::getUserInfo(UserInfo &) {
    
}

int Response::getGroupName(std::string &ret) const {
    if (!root.isMember("groupName") || !root["groupName"].isString())
        return ERROR;
    ret = root["groupName"].asString();
    return 0;
}

int Response::getGroupID() const {
    if (!root.isMember("groupID") || !root["groupID"].isInt())
        return ERROR;
    return root["groupID"].asInt();
}
*/
/*
int Response::getUserInfo(std::string &rawString, UserInfo &ui) const {
    Json::Value root;
    if (stringToJson(rawString, root) == ERROR)
        return ERROR;
    for (__typeof(
}
*/

Response::Response(std::string &s) {
    stringToJson(s, root);
}

int Response::getStatus() const {
    return root["status"].asInt();
}

int Response::getUserInfo(UserInfo &ui) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        for (__typeof(json.begin()) it = json.begin(); it != json.end(); it++)
            ui[it.key().asString()] = (*it).asString();
    } catch (...)  {
        return ERROR;
    }
    return 0;
}

int Response::getUserName(std::string &ret) const {
    try {
        Json::Value json = root["result"][0U]["value"];
        ret = json.asString();
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
            gpl.push_back(make_pair(json[i][0U].asInt(), json[i][0U].asString()));
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

int Response::getUserInfo(std::string &s, UserInfo &ui) const {
    Json::Value root;
    stringToJson(s, root);
    try {
        Json::Value json = root["result"][0U]["value"];
        for (__typeof(json.begin()) it = json.begin(); it != json.end(); it++)
            ui[it.key().asString()] = (*it).asString();
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
        ret = json.asString();
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
            gpl.push_back(make_pair(json[i][0U].asInt(), json[i][0U].asString()));
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

