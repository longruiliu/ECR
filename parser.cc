/*
  Protocol parser module
*/

#include <json/json.h>
#include "parser.h"

std::string jsonToString(Json::Value &);
Json::Value stringToJson(std::string &);
Request jsonToRequest(Json::Value &);
Json::Value requestToJson(Request &);

std::string jsonToString(Json::Value &json) {
    Json::FastWriter writer;
    return writer.write(json);
}

Json::Value stringToJson(std::string &str) {
    Json::Reader reader;
    Json::Value ret;
    if (reader.parse(str, ret))
        // add a "ERROR" property for the result json obj
        ret["ERROR"] = "false";
    else
        ret["ERROR"] = "true";
    return ret;
}

Request stringToRequest(std::string str) {
    Json::Value json = stringToJson(str);
    Request ret;
    if (json["ERROR"] == "true") {
        ret.sessionID = -1;
    } else {
        ret.sessionID = json["sessionID"].asInt();
        ret.op = json["op"].asInt();
        ret.payload = json["payload"].asString();
    }
    return ret;
}

Json::Value requestToJson(Request &req) {
    Json::Value ret;
    ret["sessionID"] = req.sessionID;
    ret["op"] = req.op;
    ret["payload"] = req.payload;
    return ret;
}


void retUserInfo(std::map <std::string, std::string> &ui) {
    Json::Value json;
    for (__typeof(ui.begin()) it = ui.begin(); it != ui.end(); it++)
        json[it->first] = ui[it->second];
    std::string ret = jsonToString(json);
    // call lower level function for delivery
}

void reqHandler(int token, std::string str)
{
    Request req = stringToRequest(str);
    switch (req.op) {
    }
}

