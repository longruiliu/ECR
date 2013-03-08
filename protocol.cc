/*
  Protocol layer module
*/
#include "logic/logic.h"
#include "logic/sessionControl"
#include <json/json.h>
#include <vector>
#include <string>
#include "protocol.h"

static int jsonToString(Json::Value &, std::string &);
static int stringToJson(std::string &, Json::Value &);

static int jsonToString(Json::Value &root, std::string &ret) {
    Json::FastWriter writer;
    ret = writer.write(root);
}

static int stringToJson(std::string &str, Json::Value &root) {
    Json::Reader reader;
    if (!reader.parse(str, root))
        return ERROR;
    return 0;
}

int requestHandler(std::string &request) {
    Json::Value root;
    if (stringToJson(request, root) == ERROR)
        return INVALID_REQUEST;
    // call logic layer module
    int sessionID;

    if (root["sessionID"])
        sessionID = root["sessionID"].asInt();
    else
        return ERR_SESSIONID_EXPECTED;

    if (!root["type"])
        return ERR_TYPE_EXPECTED;

    if(!root["method"])
        return ERR_METHOD_EXPECTED;

    // check sessionID

    if (root["type"] == "group") {
        switch (root["method"]) {
        case "add":
            addGroup(srcID, groupName);
            break;
        case "del":
            delGroup(srcID, groupID);
            break;
        case "adduser":
            addGroupMember(srcID, groupID, newmemberID, msg);
            break;
        case "deluser":
            delGroupMember(srcID, groupID, memberID);
            break;
        case "sendmsg":
        case "joinreq":
        case "quitreq":
        case "userlist":
        case "redmsg":
        default: return ERR_INVALID_METHOD;
        }
    } else if (root["type"] == "regular") {
        switch (root["method"]) {
        case "login":
        case "logout":
        case "sendmsg":
        case "userlist":
        case "userinfo":
        case "add":
        case "modify":
        case "del":
        case "keep-alive":
        case "fetch":
        default: return ERR_INVALID_METHOD;
        }
    } else
        return ERR_INVALID_TYPE;
    return 0;
}

