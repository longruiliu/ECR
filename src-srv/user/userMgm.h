#ifndef _USERMGM_H_
#define _USERMGM_H_ 
#include<vector>
#include<string>
std::vector<user> userList;

user& findUser(int userID);

void addUser(const std::string& userName, const std::string& passwd, const std::string& userInfo);
#endif /* _USERMGM_H_ */
