/***********************************************************************
 * Module:  groupManager.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:01:22 PM
 * Purpose: Declaration of the class groupManager
 ***********************************************************************/

#if !defined(__ServerLogic_groupManager_h)
#define __ServerLogic_groupManager_h

class group;

#include <group/group.h>

int addGroup(std::string groupName, int creatorID);
void delGroup(int groupID);
group& findGroup(int groupID);
group& findGroup(std::string groupName);


void lockGrouplist();
void releaseGrouplist();
extern std::vector<group> groupList;

#endif
