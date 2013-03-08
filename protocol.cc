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

static int getLines(std::string lines, std::vector <std::string> &line) {
    int prev = 0, len = lines.size();
    for (int i = 0; i != len; i++) {
        if (lines[i] == '\n') {
            if (i-prev)
                line.push_back(lines.substr(prev, i-prev));
            prev = i+1;
        }
    }
    if (len-1-prev)
        line.push_back(lines.substr(prev, len-1-prev));
    return line.size();
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
            if (getLines(params, argv) != 3)
                return ERR_INVALID_PARAMS;
            int groupID, newMemberID;
            sscanf(argv[0].c_str(), "%d", &groupID);
            sscanf(argv[1].c_str(), "%d", &newMemberID);
            std::string msg = argv[2];
            addGroupMember(srcID, groupID, newMemberID, msg);
        } else if (method == "deluser") {
            Args argv;
            int groupID, memberID;
            if (getLines(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            sscanf(argv[0].c_str(), "%d", &groupID);
            sscanf(argv[1].c_str(), "%d", &memberID);
            delGroupMember(srcID, groupID, memberID);
        } else if (method == "sendmsg") {
            Args argv;
            if (getLines(params, argv) != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            sscanf(argv[0].c_str(), "%d", &groupID);
            std::string msg = argv[1];
            sendGroupMsg(srcID, groupID, msg);
        } else if (method == "joinreq") {
        } else if (method =="quitreq") {
        } else if (method == "userlist") {
        } else if (method == "redmsg") {
        } else
            return ERR_INVALID_METHOD;
    } else if (root["type"] == "regular") {
        if (method == "login") {
        } else if (method == "logout") {
        } else if (method == "sendmsg") {
        } else if (method == "userlist") {
        } else if (method == "userinfo") {
        } else if (method == "add") {
        } else if (method == "modify") {
        } else if (method == "del") {
        } else if (method == "keep-alive") {
        } else if (method == "fetch") {
        } else
            return ERR_INVALID_METHOD;
    } else
        return ERR_INVALID_TYPE;
    return 0;
}

