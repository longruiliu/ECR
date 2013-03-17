/***********************************************************************
 * Module:  group.cpp
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Implementation of the class group
 ***********************************************************************/
#include <iostream>
#include "group.h"

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

group::group(const std::string& name, int creator,const std::string &info = "null")
{
	groupName = name;
	creatorID = creator;
	groupInfo = info;
}
