#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <msgRecord.h>

const int ERROR = ~0;

typedef std::map <std::string, std::string> UserInfo;

class Wrapper;

class Request {
    friend class Wrapper;
public:
    int setSessionID(int);
    int setType(std::string &);
    int setMethod(std::string &);
    /* Params must be ordered as protocol defines */
    int addParams(std::string &);
    int addParams(int);
    int addParams(UserList &);
private:
    Json::Value root;
};

class Response {
public:
    int getUserInfo(UserInfo &) const;
    int getSessionID() const;
    int getUserList(UserList &) const;
    int getGroupName(std::string &) const;
    int getGroupID() const;
    int getMsg(std::vector <msgRecord> &) const;
    int getUserInfo(UserInfo &) const;
private:
    Json::Value root;
};

int sendRequest(Request &, Response &);

#endif
