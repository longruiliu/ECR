/*
  Protocol layer module
*/

#include <json/json.h>
#include <cstdio>
#include <vector>
#include <string>
#include <user.h>
#include <protocol.h>
#include <groupMsg.h>
#include <group.h>
#include <logic.h>
#include <msgRecord.h>
#include <network.h>
#include <net.h>
#include <serial.h>
#include <proto.h>


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
int sendResponse(Json::Value &root) {
    std::string ret;
    jsonToString(root, ret);
}
*/

int requestHandler(std::string &request) {
    Json::Value root;
    if (stringToJson(request, root) == ERROR)
        return ERR_INVALID_REQUEST;
    // call logic layer module
    
    int req_sessionID = root.get("sessionID", 0).asInt();
    std::string req_type = root.get("type", "").asString();
    std::string req_method = root.get("method", "").asString();
    Json::Value req_params = root.["params"];

    // check sessionID

    int srcID = getUserIDBySession(req_sessionID);

    if (root["type"] == "group") {
        if (method == "add") {
            std::string groupName = params[0U]["value"].asString();
            addGroup(srcID, groupName);
        } else if (method == "del") {
            int groupID;
            groupID = params[0U].asInt();
            delGroup(srcID, groupID);
        } else if (method == "adduser") {
            if (params.size() != 3)
                return ERR_INVALID_PARAMS;
            int groupID, newMemberID;
            groupID = params[0U].asInt();
            newMemberID = params[0U].asInt();
            std::string msg = params[2].asString();
            addGroupMember(srcID, groupID, newMemberID, msg);
        } else if (method == "deluser") {
            int groupID, memberID;
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            groupID = params[0U].asInt();
            memberID = params[1U].asInt();
            delGroupMember(srcID, groupID, memberID);
        } else if (method == "sendmsg") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            groupID = params[0U].asInt();
            std::string msg = params[1].asString();
            sendGroupMsg(srcID, groupID, msg);
        } else if (method == "joinreq") {
        } else if (method =="quitreq") {
        } else if (method == "userlist") {
            int groupID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            groupID = params[0U].asInt();
            fetchMemberList(srcID, groupID);
        } else if (method == "redmsg") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int groupID;
            groupID = params[0U].asInt();
            std::string msg = params[1].asString();
            sendGroupMsg(srcID, groupID, msg);
        } else
            return ERR_INVALID_METHOD;
    } else if (root["type"] == "regular") {
        if (method == "login") {
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            int userID, IP;
            std::string passwd;
            userID = params[0U].asInt();
            passwd = params[1U].asString();
            login(userID, passwd, IP);
        } else if (method == "logout") {
            logout(srcID);
        } else if (method == "sendmsg") {
            int dstID;
            std::string msg;
            if (params.size() != 2)
                return ERR_INVALID_PARAMS;
            dstID = params[0U].asInt();
            msg = params[1U].asString();
            sendMsg(srcID, dstID, msg);
        } else if (method == "userlist") {
        } else if (method == "userinfo") {
            int dstID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            dstID = params[0U].asInt();
            getUserInfo(srcID, dstID);
        } else if (method == "add") {
            std::string userName, passwd, userInfo;
            //std::map<std::string, std::string> userInfo;
            if (params.size() != 3)
                return ERR_INVALID_PARAMS;
            userName = params[0U].asString();
            passwd = params[1U].asString();
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(params[2U].asString(), root))
                return ERR_INVALID_PARAMS;
            /*if (jsonToMap(root, userInfo) == ERROR)
              return ERR_INVALID_PARAMS;*/
            addUser(srcID, userName, passwd, userInfo);
        } else if (method == "modify") {
            int userID;
            std::string newName, newPasswd, newInfo;
            //std::map <std::string, std::string> newInfo;
            if (params.size() != 4)
                return ERR_INVALID_PARAMS;
            sscanf(params[0U].asString().c_str(), "%d", &userID);
            newName = params[1U].asString();
            newPasswd = params[2U].asString();
            Json::Value root;
            Json::Reader reader;
            if (!reader.parse(params[3U].asString(), root))
                return ERR_INVALID_PARAMS;
            /*if (jsonToMap(root, newInfo) == ERROR)
              return ERR_INVALID_PARAMS;*/
            modifyUser(srcID, userID, newName, newPasswd, newInfo);
        } else if (method == "del") {
            int userID;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            userID = params[0U].asInt();
            delUser(srcID, userID);
        } else if (method == "keepalive") {
        } else if (method == "fetch") {
            time_t since;
            if (params.size() != 1)
                return ERR_INVALID_PARAMS;
            since = params[0U].asInt();
            fetchMsg(srcID, since);
        } else
            return ERR_INVALID_METHOD;
    } else
        return ERR_INVALID_TYPE;
    return 0;
}

