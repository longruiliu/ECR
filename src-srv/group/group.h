/***********************************************************************
 * Module:  group.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Declaration of the class group
 ***********************************************************************/

#if !defined(__ServerLogic_group_h)
#define __ServerLogic_group_h

class groupMsg;
class user;

#include "groupMsg.h"
#include<vector>

class group
{
public:
	void getMsg(time_t since);
	bool isInGroup(int userID);
	int postMsg(int srcID,const std::string& msg);

	void addUser(int userID);
	void delUser(int UserID);

	group(const std::string& name, int creator);
	//group(* sDB, int gID);

	int groupID;
 	std::string groupName;
 	int creatorID;
 	time_t lastMsgTime;
 	time_t oldestMemTime;

 	std::vector<groupMsg> msgList;
	std::vector<int> groupMember;

	#ifdef DEBUG
	void printUserList();
	void printMsgList();
	#endif

protected:
private:
	void lockGroup();
	void releaseGroup();
};

#endif
