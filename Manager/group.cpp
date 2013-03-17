/***********************************************************************
 * Module:  group.cpp
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Implementation of the class group
 ***********************************************************************/
#include <iostream>
#include "group.h"
#include "Database.h"

group::group()
{
	groupName = "";
	creatorID = 0;
	groupInfo = "null";
}

group::group(const group &other)
{
	groupID = other.groupID;
	creatorID = other.creatorID;
	groupName = other.groupName;
	groupInfo = other.groupInfo;
	groupMember = other.groupMember;
}

group::group(const std::string& name, int creator)
{
    int gid = rand()%10000;
    while(hasGroup(gid))
            gid = rand()%10000;
    groupID = gid;
    groupName = name;
    creatorID = creator;
}

bool group::hasGroup(int gid)
{
    for (glit i = groupList.begin();i !=groupList.end();i++)
        if (i->groupID == gid)
            return true;
    return false;
}
