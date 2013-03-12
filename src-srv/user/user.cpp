#include "user.h"

#ifdef DEBUG
#include <iostream>
void user::printUser()
{
	std::cout << "  " << userID << std::endl;
}

#endif

user::user(int id,const std::string &name,const std::string &password,int pre,const std::string &infomation,int addr)
{
	userID = id;
	userName = name;
	pwd = password;
	previlege = pre;
	info = infomation;
	IP = addr;
}
