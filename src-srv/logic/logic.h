#ifndef _LOGIC_H_
#define _LOGIC_H_ 

#include<string>
#include<map>

//Group
int sendGroupMsg(int sessionID, int groupID, const std::string& msg);
int sendRedMsg(int sessionID, int groupID, const std::string& msg);

int addGroupMember(int sessionID,int groupID, int newMemberID, std::const string& msg);
int delGroupMember(int sessionID, int groupID, int memberID);

int fetchMemberList(int sessionID, int groupID);
int fetchGroupMsg(int sessionID, int groupID, time_t since);

//User Control
int login(int userID, const std::string& passwd);
int logout(int sessionID);


int getUserInfo(int sessionID, int dstID);

int addUser(int sessionID, const std::string& userName, const std::string& passwd, const std::map<string, string>& userInfo);
int modifyUser(int sessionID, int userID, const std::string& newName, const std::string& newPasswd, const std::map<string, string>& newInfo); 
int delUser(int sessionID, int userID);

//P2P
int sendMsg(int sessionID, int dstID, const std::string& msg);
int fetchMsg(int sessionID, time_t since);
#endif /* _LOGIC_H_ */
