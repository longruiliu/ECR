/***********************************************************************
 * Module:  group.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Declaration of the class group
 ***********************************************************************/

#if !defined(__ServerLogic_group_h)
#define __ServerLogic_group_h

class user;

#include<vector>
#include<string>

class group
{
public:
	group();
	group(const group &other);
	group(const std::string& name, int creator,const std::string& info);

	int groupID;
 	int creatorID;
 	std::string groupName;
        std::string groupInfo;

	std::vector<int> groupMember;
protected:
private:
};

#endif
