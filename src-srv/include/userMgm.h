#ifndef _USERMGM_H_
#define _USERMGM_H_ 
#include<vector>
#include<string>
#include"user.h"

extern void lockUserlist();
extern void releaseUserlist();
extern std::vector<user> userList;

extern user& findUser(int userID);

void addUser(const std::string& userName, const std::string& passwd, const std::string& userInfo);
#endif /* _USERMGM_H_ */
