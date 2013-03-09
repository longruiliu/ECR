/*
  Protocol layer module
*/

#include <json/json.h>
#include <cstdio>
#include <vector>
#include <string>
#include "protocol.h"
#include "src-srv/logic/sessionControl.h"
#include "src-srv/logic/logic.h"

static int jsonToString(Json::Value &, std::string &);
static int stringToJson(std::string &, Json::Value &);

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

static int jsonToMap(Json::Value &root, std::map <std::string, std::string> &ret) {
    for (__typeof(root.begin()) it = root.begin(); it != root.end(); it++) {
        if (it.key().isString() && (*it).isString())
            ret[it.key().asString()] = (*it).asString();
        else
            return ERROR;
    }
    return 0;
}

/*
  static int getParams(std::string lines, std::vector <std::string> &line, int limit = LINE_MAX) {
    int prev = 0, len = lines.size(), cnt = 0;
    for (int i = 0; i != len && cnt < limit; i++) {
        if (lines[i] == '\n') {
            if (i-prev) {
                line.push_back(lines.substr(prev, i-prev));
                cnt++;
            }
            prev = i+1;
        }
    }
    if (len-1-prev>0) {
        line.push_back(lines.substr(prev, len-1-prev));
        cnt++;
    }
    return cnt;
}
*/

int requestHandler(std::string &request) {
    Json::Value root;
    if (stringToJson(request, root) == ERROR)
        return ERR_INVALID_REQUEST;
    // call logic layer module

    int sessionID;
    if (root.isMember("sessionID"))
        sessionID = root["sessionID"].asInt();
    else
        return ERR_SESSIONID_EXPECTED;

    if (!root.isMember("type"))
        return ERR_TYPE_EXPECTED;

    if(!root.isMember("method"))
        return ERR_METHOD_EXPECTED;

    // check sessionID

    int srcID = sessionID;
    if (!root["params"].isArray())
        return ERR_INVALID_PARAMS;
    Json::Value params = root["params"];
    std::string method = root["method"].asString();

    if (root["type"] == "group") {
        if (method == "add") {
            std::string groupName = params[0U].asString();
            addGroup(srcID, groupName);
        } else if (method == "del") {
            int groupID;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            delGroup(srcID, groupID);
        } else if (method == "adduser") {
            if (params.size() != 3)
                return ERR_INVALID_PARAMS;
            int groupID, newMemberID;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            sscanf(params[1U].asString().c_str(), "%d", &newMemberID);
            std::string msg = params[2].asString();
            addGroupMember(srcID, groupID, newMemberID, msg);
        } else if (method == "deluser") {
            int groupID, memberID;
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            sscanf(params[1U].asString().c_str(), "%d", &memberID);
            delGroupMember(srcID, groupID, memberID);
        } else if (method == "sendmsg") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            std::string msg = params[1].asString();
            sendGroupMsg(srcID, groupID, msg);
        } else if (method == "joinreq") {
        } else if (method =="quitreq") {
        } else if (method == "userlist") {
            int groupID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            fetchMemberList(srcID, groupID);
        } else if (method == "redmsg") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            sscanf(params[0U].asString().c_str(), "%d", &groupID);
            std::string msg = params[1].asString();
            sendGroupMsg(srcID, groupID, msg);
        } else
            return ERR_INVALID_METHOD;
    } else if (root["type"] == "regular") {
        if (method == "login") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int userID;
            std::string passwd;
            sscanf(params[0U].asString().c_str(), "%d", &userID);
            passwd = params[1U].asString();
            login(userID, passwd);
        } else if (method == "logout") {
            logout(srcID);
        } else if (method == "sendmsg") {
            int dstID;
            std::string msg;
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &dstID);
            msg = params[1U].asString();
            sendMsg(srcID, dstID, msg);
        } else if (method == "userlist") {
        } else if (method == "userinfo") {
            int dstID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &dstID);
            getUserInfo(srcID, dstID);
        } else if (method == "add") {
            std::string userName, passwd;
            std::map<std::string, std::string> userInfo;
            if (params.size() != 3)
                return ERR_INVALID_PARAMS;
            userName = params[0U].asString();
            passwd = params[1U].asString();
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(params[2U].asString(), root))
                return ERR_INVALID_PARAMS;
            if (jsonToMap(root, userInfo) == ERROR)
                return ERR_INVALID_PARAMS;
            addUser(srcID, userName, passwd, userInfo);
        } else if (method == "modify") {
            int userID;
            std::string newName, newPasswd;
            std::map <std::string, std::string> newInfo;
            if (params.size() != 4)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &userID);
            newName = params[1U].asString();
            newPasswd = params[2U].asString();
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(params[3U].asString(), root))
                return ERR_INVALID_PARAMS;
            if (jsonToMap(root, newInfo) == ERROR)
                return ERR_INVALID_PARAMS;
            modifyUser(srcID, userID, newName, newPasswd, newInfo);
        } else if (method == "del") {
            int userID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &userID);
            delUser(srcID, userID);
        } else if (method == "keep-alive") {
        } else if (method == "fetch") {
            time_t since;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%u", &since);
            fetchMsg(srcID, since);
        } else
            return ERR_INVALID_METHOD;
    } else
        return ERR_INVALID_TYPE;
    return 0;
}

