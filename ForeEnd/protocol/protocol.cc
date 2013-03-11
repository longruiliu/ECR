/*
  Protocol layer module
*/

#include <json/json.h>
#include <map>
#include <string>
#include <cstdio>
#include "protocol.h"

static int jsonToString(Json::Value &, std::string &);
static int stringToJson(std::string &, Json::Value &);
static std::string serialUserInfo(UserInfo &);
static std::string serialUserList(UserList &);
static std::string intToString(int);
static int stringToInt(std::string);

class Wrapper {
public:
    std::string wrap(Json::Value root) {
        std::string ret;
        if (jsonToString(root, ret))
            return ret;
        return "";
    }
};

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

static std::string serialUserInfo(UserInfo &ui) {
    Json::Value root;
    for (__typeof(ui.begin()) it = ui.begin(); it != ui.end(); it++)
        root[it->first] = it->second;
    std::string ret;
    if (jsonToString(root, ret))
        return ret;
    return "";
}

int Request::setSessionID(int val) {
    std::string sessionID = intToString(val);
    root["sessionID"] = sessionID;
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
    std::string t = intToString(val);
    root["params"].append(t);
    return 0;
}

int Request::addParams(std::string &s) {
    root["params"].append(s);
    return 0;
}

int Request::addParams(UserInfo &ui) {
    std::string ret = serialUserInfo(ui);
    root["params"].append(ret);
    return 0;
}

int Request::addParams(UserList &ul) {
    std::string ret = serialUserList(ul);
    root["params"].append(ret);
    return 0;
}

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

int sendRequest(Request &request, Response &response) {
    Wrapper Wrapper;
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
    if (!root.isMember("sessionID") || !root["sessionID"].isString())
        return ERROR;
    return stringToInt(root["sessionID"].asString());
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

int Response::getGroupName(std::string &ret) const {
    if (!root.isMember("groupName") || !root["groupName"].isString())
        return ERROR;
    ret = root["groupName"].asString();
    return 0;
}

int Response::getGroupID() const {
    if (!root.isMember("group") || !root["groupID"].isString())
        return ERROR;
    return stringToInt(root["groupID"].asString());
}
