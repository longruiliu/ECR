#include "group/group.h"
#include "group/groupManager.h"

int addGroupMember(int srcID,int groupID, int newMemberID, std::const string& msg)
{
  user u = findUser(srcID);
  group p = findGroup(groupID);
  //Privilige Check
  //User is creator of group or
  // user is root
  if (u.
}

