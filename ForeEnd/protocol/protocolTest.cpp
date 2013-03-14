#include <json/json.h>
#include <map>
#include <iostream>
#include <string>
#include <cstdio>
#define ERROR -1


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

int main()
{
    Json::Value root;
    for (int i = 0; i < 10; i++)
        root["params"].append(i);
    std::string ret;
    if (jsonToString(root,ret) == 0)
        std::cout << ret << std::endl;
    return 0;
}
