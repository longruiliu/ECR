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

const int LINE_MAX = 10;
typedef std::vector <std::string> Args;

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
    std::string params = root.get("params", "").asString();
    std::string method = root.get("method", "").asString();

    if (root["type"] == "group") {
        if (method == "add") {
            std::string groupName = params;
            addGroup(srcID, groupName);
        } else if (method == "del") {
            int groupID;
            sscanf(params.c_str(), "%d", &groupID);
            delGroup(srcID, groupID);
        } else if (method == "adduser") {
            Args argv;
            if (getParams(params, argv) != 3)
                return ERR_INVALID_PARAMS;
            int groupID, newMemberID;
            sscanf(argv[0].c_str(), "%d", &groupID);
            sscanf(argv[1].c_str(), "%d", &newMemberID);
            std::string msg = argv[2];
            addGroupMember(srcID, groupID, newMemberID, msg);
        } else if (method == "deluser") {
            Args argv;
            int groupID, memberID;
            if (getParams(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            sscanf(argv[0].c_str(), "%d", &groupID);
            sscanf(argv[1].c_str(), "%d", &memberID);
            delGroupMember(srcID, groupID, memberID);
        } else if (method == "sendmsg") {
            Args argv;
            if (getParams(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            sscanf(argv[0].c_str(), "%d", &groupID);
            std::string msg = argv[1];
            sendGroupMsg(srcID, groupID, msg);
        } else if (method == "joinreq") {
        } else if (method =="quitreq") {
        } else if (method == "userlist") {
            int groupID;
            sscanf(params.c_str(), "%d", &groupID);
            fetchMemberList(srcID, groupID);
        } else if (method == "redmsg") {
            Args argv;
            if (getParams(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            sscanf(argv[0].c_str(), "%d", &groupID);
            std::string msg = argv[1];
            sendGroupMsg(srcID, groupID, msg);
        } else
            return ERR_INVALID_METHOD;
    } else if (root["type"] == "regular") {
        if (method == "login") {
            Args argv;
            if (getParams(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            int userID;
            std::string passwd;
            sscanf(argv[0].c_str(), "%d", &userID);
            passwd = argv[1];
            login(userID, passwd);
        } else if (method == "logout") {
            logout(srcID);
        } else if (method == "sendmsg") {
            int dstID;
            std::string msg;
            Args argv;
            if (getParams(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            sscanf(argv[0].c_str(), "%d", &dstID);
            msg = argv[1];
            sendMsg(srcID, dstID, msg);
        } else if (method == "userlist") {
        } else if (method == "userinfo") {
            int dstID;
            sscanf(params.c_str(), "%d", &dstID);
            getUserInfo(srcID, dstID);
        } else if (method == "add") {
            std::string userName, passwd;
            std::map<std::string, std::string> userInfo;
            Args argv;
            if (getParams(params, argv, 2) != 3)
                return ERR_INVALID_PARAMS;
            userName = argv[0];
            passwd = argv[1];
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(argv[2], root))
                return ERR_INVALID_PARAMS;
            if (jsonToMap(root, userInfo) == ERROR)
                return ERR_INVALID_PARAMS;
            addUser(srcID, userName, passwd, userInfo);
        } else if (method == "modify") {
            int userID;
            std::string newName, newPasswd;
            std::map <std::string, std::string> newInfo;
            Args argv;
            if (getParams(params, argv, 3) != 4)
                return ERR_INVALID_PARAMS;
            sscanf(argv[0].c_str(), "%d", &userID);
            newName = argv[1];
            newPasswd = argv[2];
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(argv[3], root))
                return ERR_INVALID_PARAMS;
            if (jsonToMap(root, newInfo) == ERROR)
                return ERR_INVALID_PARAMS;
            modifyUser(srcID, userID, newName, newPasswd, newInfo);
        } else if (method == "del") {
            int userID;
            sscanf(params.c_str(), "%d", &userID);
            delUser(srcID, userID);
        } else if (method == "keep-alive") {
        } else if (method == "fetch") {
            time_t since;
            sscanf(params.c_str(), "%u", &since);
            fetchMsg(srcID, since);
        } else
            return ERR_INVALID_METHOD;
    } else
        return ERR_INVALID_TYPE;
    return 0;
}

