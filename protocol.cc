/*
  Protocol layer module
*/

#include <json/json.h>
#include <vector>
#include "protocol.h"

int jsonToString(Json::Value &, std::string &);
int stringToJson(std::string &, Json::Value &);

int jsonToString(Json::Value &json, std::string &ret) {
    Json::FastWriter writer;
    ret = writer.write(json);
}

int stringToJson(std::string &str, Json::Value &json) {
    Json::Reader reader;
    if (!reader.parse(str, json)) return ERROR;
    return 0;
}

int requestHandler(std::string &request, std::string &response)
{
    Json::Value json;
    if (stringToJson(request, json) == ERROR)
        return INVALID_REQUEST;
}
