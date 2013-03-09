/***********************************************************************
 * Module:  user.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 2:52:10 PM
 * Purpose: Declaration of the class user
 ***********************************************************************/

#if !defined(__ServerLogic_user_h)
#define __ServerLogic_user_h

class user
{
public:
  static time_t keepAliveIntv;
	int userID;
	string userName;
	string pwd;
	int previlege;
	string info;
	int privMask;
	int IP;
  time_t lastKA;

  //Privilege query
  bool canUserMg();
  bool canGroupMg();

  bool needClean();
  std::vector<msgRecord> msgList;
#ifdef DEBUG
	void printUser();
#endif
};

user& findUser(int userID);

#endif
