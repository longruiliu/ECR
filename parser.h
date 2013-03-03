#ifndef __PARSER_H
#define __PARSER_H

#include <string>
#include <vector>

void retUserList(vector <UserInfo> &);
void retMsgList(vector <groupMsg> &);
void retSessionID(int);
void retGroupID(int);
void retUserInfo(map <std:string, std::string> &);

struct Request {
    int sessionID, op;
    std::string payload;
};

struct Response {
    int statusID;
    std::string payload;
};


#endif
