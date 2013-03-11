#ifndef _LOGIC_H_
#define _LOGIC_H_ 

#include<string>
#include<map>

//Group
int sendGroupMsg(int srcID, int groupID, const std::string& msg);
int sendRedMsg(int srcID, int groupID, const std::string& msg);

int addGroup(int srcID, const std::string& groupName);
int delGroup(int srcID, int groupID);

int addGroupMember(int srcID,int groupID, int newMemberID, const std::string& msg); //Coded, not test
int delGroupMember(int srcID, int groupID, int memberID);

int fetchMemberList(int srcID, int groupID);
int fetchGroupMsg(int srcID, int groupID, time_t since);

//User Control
int login(int userID, const std::string& passwd);
int logout(int srcID);


int getUserInfo(int srcID, int dstID);

int addUser(int srcID, const std::string& userName, const std::string& passwd, const std::string& userInfo);
int modifyUser(int srcID, int userID, const std::string& newName, const std::string& newPasswd, const std::string& newInfo); 
int delUser(int srcID, int userID);

//P2P
int sendMsg(int srcID, int dstID, const std::string& msg);
int fetchMsg(int srcID, time_t since);

enum {
    ERR_SESSIONID_EXPECTED,
    ERR_METHOD_EXPECTED,
    ERR_TYPE_EXPECTED,
    ERR_PARAMS_EXPECTED,
    ERR_INVALID_METHOD,
    ERR_INVALID_PARAMS,
    ERR_INVALID_TYPE,
    ERR_OK,
    ERR_NOT_IN_GROUP,
    ERR_NO_PRIVILEGE
};
#endif /* _LOGIC_H_ */
