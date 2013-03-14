#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <msgRecord.h>
#include <network.h>

const int ERROR = ~0;

/*
  Data types that transport through net:
  UserID
  UserName
  UserInfo
  UserList
  GroupID
  GroupName
  MsgList
*/

typedef msgRecord MsgRecord;
typedef std::map <std::string, std::string> UserInfo;
typedef std::vector <int> UserList;
typedef std::vector <MsgRecord> MsgList;

class Request {
public:
    int setSessionID(int);
    int setType(std::string &);
    int setMethod(std::string &);
    /* Params must be ordered as protocol defines */
    int addParams(std::string &);
    int addParams(int);
    int addParams(UserList &);
    int addParams(UserInfo &);
    int addParams(MsgList &);
    int encode(std::string &rawString);
private:
    Json::Value root;
};

class Response {
public:
    int getStatus() const;
    int getUserInfo(std::string &rawString, UserInfo &ui) const;
    int getUserName(std::string &rawString, std::string &) const;
    int getUserID(std::string &rawString) const;
    int getSessionID(std::string &rawString) const;
    int getUserList(std::string &rawString, UserList &ul) const;
    int getGroupName(std::string &rawString, std::string &groupName) const;
    int getGroupID(std::string &rawString) const;
    int getMsgList(std::string &rawString, std::vector <msgRecord> &) const;
};

#endif
