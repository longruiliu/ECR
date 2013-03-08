/*
  Protocol layer module
*/

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

int requestHandler(std::string &request, std::string &response) {
    Json::Value root;
    if (stringToJson(request, root) == ERROR)
        return INVALID_REQUEST;
    // call logic layer module
    return 0;
}

