#include <json>
#include "parser.h"

string jsonToString(Json::value &);
Json::value stringToJson(std::string &);
Request jsonToRequest(Json::value &);
Json::Value requestToJson(Request &);

