/***********************************************************************
 * Module:  user.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 2:52:10 PM
 * Purpose: Declaration of the class user
 ***********************************************************************/

#if !defined(__ServerLogic_user_h)
#define __ServerLogic_user_h

#include<string>
#include<vector>
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
        std::vector<msgRecord> msgList;

  //Privilege query
  user(int,const std::string&,const std::string &,int,const std::string &,int);
  bool canUserMg();
  bool canGroupMg();
  bool isRoot();

  
  void pushNotify(int type, int extra);
  void sendMsg(int srcID, const std::string& msg);
#ifdef DEBUG
	void printUser();
#endif
};


#endif
