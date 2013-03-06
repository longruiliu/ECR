/*
  Protocol layer module
*/

#include <json/json.h>
#include <vector>
#include "protocol.h"

std::string jsonToString(Json::Value &);
Json::Value stringToJson(std::string &);

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

int reqHandler(std::string &request, std::string &response)
{
    
}
