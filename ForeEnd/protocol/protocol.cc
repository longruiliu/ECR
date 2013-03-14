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

int Request::getType(std::string &type){
	type = root["type"];
	return 0;
}

int Request::getMethod(std::string &method){
	method = root["method"];
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
    Json::param;
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
        msg["postTime"] = ml[i].postTime;
        msg["msgType"] = ml[i].msgType;
        arr.append(msg);
    }
    param["value"] = arr;
    root["params"].append(param);
}

int Request::encode(std::string &rawString) {
    return stringToJson(rawString, root);
}


void Response::setRawData(std::string &rawData){
    stringToJson(rawData, root);
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


int Response::getUserInfo(UserInfo &ui) {
    
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

