/***********************************************************************
 * Module:  groupManager.cpp
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Implementation of the class groupManager
 ***********************************************************************/

#include "../include/group.h"
#include "../include/groupManager.h"
#include "../include/dbSync.h"

std::vector<group> groupList;


int addGroup(std::string groupName, int creatorID)
{
	groupList.push_back(group(groupName, creatorID));
}

void delGroup(int groupID)
{
	for(auto i = groupList.begin(); i != groupList.end();)
	{
		if (i->groupID == groupID)
			i = groupList.erase(i);
		else
			i++;
	}
}

group& findGroup(int groupID)
{
	for(auto i = groupList.begin(); i != groupList.end();)
	{
		if (i->groupID == groupID)
			return *i;
		else
			i++;
	}
}

group& findGroup(std::string groupName)
{
	for(auto i = groupList.begin(); i != groupList.end();i++)
	{
		if (i->groupName == groupName)
			return *i;
		else
			i++;
	}
}
