#include <json/json.h>
#include <map>
#include <string>
#include <iostream>

static int jsonToMap(Json::Value &root, std::map <std::string, std::string> &ret) {
    for (__typeof(root.begin()) it = root.begin(); it != root.end(); it++) {
        if (it.key().isString() && (*it).isString())
            ret[it.key().asString()] = (*it).asString();
        else {
            std::cout << "ERROR" <<std::endl;
            return -1;
        }
    }
    return 0;
}

void test() {
    Json::Value root;
    root["first"] = "1";
    root["second"] = "2";
    for (__typeof(root.begin()) it = root.begin(); it != root.end(); it++)
        std::cout << it.key().asString() << std::endl;
}

int main() {
    test();
    return 0;
}
