#include <json>
#include "parser.h"

std::string jsonToString(Json::value &);
Json::value stringToJson(std::string &);
Request jsonToRequest(Json::value &);
Json::Value requestToJson(Request &);

std::string jsonToString(Json::value &json) {
    Json::FastWriter writer;
    return writer.write(json);
}

Json::Value stringToJson(std::string &str) {
    Json::reader reader;
    Json::Value ret;
    if (reader.parse(str, ret))
        // add a "ERROR" property for the result json obj
        ret["ERROR"] = "true";
    else
        ret["ERROR"] = "false";
    return ret;
}

Request jsonToRequest(Json::value &json) {
    
}

Json::Value requestToJson(Request &req) {
    Json::Value ret;
    ret["sessionID"] = req.sessionID;
    ret["op"] = req.op;
    ret["payload"] = req.payload;
    return ret;
}


void retUserInfo(map <std::string, std::string> &ui) {
    Json::Value json;
    for (__typeof(ui.begin()) it = ui.begin(); it != ui.end(); it++)
        json[*it.first] = ui[*it.second];
    std::string ret = jsonToString(json);
    // call lower level function for delivery
}



