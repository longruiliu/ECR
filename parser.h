#ifndef __PARSER_H
#define __PARSER_H
#include <string>
#include <vector>
void retUserList(vector <UserInfo> &);
struct Request {
    int sessionID, op;
    std::string payload;
};
#endif
