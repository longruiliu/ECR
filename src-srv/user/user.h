/***********************************************************************
 * Module:  user.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 2:52:10 PM
 * Purpose: Declaration of the class user
 ***********************************************************************/

#if !defined(__ServerLogic_user_h)
#define __ServerLogic_user_h

#include<string>
#include"../msgRecord.h"

class user
{
public:
	int userID;
	std::string userName;
	std::string pwd;
	int previlege;
	std::string info;
	int IP;

  //Privilege query
  user(int,std::string,std::string,int,std::string,int);
  bool canUserMg();
  bool canGroupMg();
  bool isRoot();

  std::vector<msgRecord> msgList;
  
  void pushNotify(int type, int extra);
  void sendMsg(int srcID, const std::string& msg);
#ifdef DEBUG
	void printUser();
#endif
};


#endif
