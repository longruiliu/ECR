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
    root["first"] = 1;
    root["second"] = 2;
    root["third"].append("fuck");
    std::cout << root.size() << std::endl;
    std::cout << root["third"].size() << std::endl;
    std::map <std::string, std::string> hash;
    jsonToMap(root, hash);
}

int main() {
    test();
    return 0;
}
