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

  //Privilege query
  bool canUserMg();
  bool canGroupMg();
  bool isRoot();

  bool needClean();
  std::vector<msgRecord> msgList;
  
  void pushNotify(int type, int extra);
  void sendMsg(int srcID, const std::string& msg);
#ifdef DEBUG
	void printUser();
#endif
};

user& findUser(int userID);

#endif
