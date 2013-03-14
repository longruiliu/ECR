#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include "msgRecord.h"

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
	int getType(std::string &);
	int getMethod(std::string &);
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
    void setRawData(std::string &rawData);
    int getStatus() const;
    int getUserInfo(UserInfo &ui) const;
    int getUserName(std::string &) const;
    int getUserID() const;
    int getSessionID() const;
    int getUserList(UserList &ul) const;
    int getGroupName(std::string &groupName) const;
    int getGroupID() const;
    int getMsgList(std::vector <msgRecord> &msgVec) const;
private:
    Json::Value root;
};

#endif
