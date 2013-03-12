/***********************************************************************
 * Module:  group.cpp
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Implementation of the class group
 ***********************************************************************/

#include "groupMsg.h"
#include <time.h>
#include "../protocol/proto.h"
#include "../user/user.h"
#include "group.h"
#include "../serial.h"
#include"../user/userMgm.h"
#include "../net.h"

#include <iostream>

void group::getMsg(time_t since)
{
	if (since >= lastMsgTime)
		return;
	if (since < oldestMemTime)
		since = oldestMemTime;

	lockGroup();
	auto i = msgList.begin();
	while(since<i->postTime && i!=msgList.end())
		i++;
	releaseGroup();

	retMsgList(std::vector<groupMsg>(i, msgList.end()));
}

bool group::isInGroup(int userID)
{
	
	for(auto i = groupMember.begin();i!=groupMember.end();i++)
		if (*i == userID)
			return true;
	return false;
}

int group::postMsg(int srcID,const std::string& msg)
{
	lockGroup();
	msgList.push_back(groupMsg(false, srcID, groupID, msg));
	releaseGroup();

	//Send notify to all group members
	for (auto i = groupMember.begin(); i != groupMember.end(); i++)
		sendNotify(findUser(*i).IP, NOTIFY_NEW_GROUP_MSG,0);
}

void group::addUser(int userID)
{
	lockGroup();
	//ToDo: Use set to avoid collision
	groupMember.push_back(userID);	
	releaseGroup();
}

void group::delUser(int userID)
{
	auto i = groupMember.begin();
	while(i!=groupMember.end())
		if (*i == userID)
		{
			lockGroup();
			i = groupMember.erase(i);
			releaseGroup();
		}
		else
			i++;
}

void group::lockGroup()
{
	return;
}

void group::releaseGroup()
{
	return;
}

group::group()
{
	groupName = "";
	creatorID = 0;
	groupInfo = "null";
}

group::group(const std::string& name, int creator,const std::string &info = "null")
{
	groupName = name;
	creatorID = creator;
	groupInfo = info;
}

/*group::group(db* sDB, int gID)
{
	
}*/

#ifdef DEBUG
void group::printUserList()
{
	for(auto i = groupMember.begin(); i != groupMember.end(); i++)
		std::cout << *i << std::endl;
}

void group::printMsgList()
{
	for(auto i = msgList.begin(); i!= msgList.end(); i++)
		i->printMsg();
}

#endif
