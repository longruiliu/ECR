#include "group.h"
#include "protocol_const.h"
#include "groupManager.h"
#include "protocol_const.h"

int addGroupMember(int srcID,int groupID, int newMemberID, std::const string& msg)
{
  user u = findUser(srcID);
  group g = findGroup(groupID);

  //Privilege Check
  //User is creator of group or
  // user is root
  if (srcID == g.creatorID)
  {
    g.addUser(newMemberID);
  }
  else
  {
    if (srcID!=newMemberID)
      return ERR_NO_PRIVILEGE;
    user creator = findUser(g.creator);
    creator.sendMsg(0, std::string("New request from ")+srcID+" to join group " + groupID+"\n"+msg);
  }

  return ERR_OK;
}

int delGroupMember(int srcID, int groupID, int memberID)
{
  user u = findUser(srcID);
  group g = findGroup(groupID);
  if (srcID == g.createID || u.isRoot())
    g.delUser(memberID);
  else
    return ERR_NO_PRIVILEGE;

  return ERR_OK;
}

int addGroup(int srcID, const std::string& groupName)
{
  user u = findUser(srcID);
  if (u.canGroupMg())
  {
      int groupID = addGroup(groupName, srcID);
      retInt(groupID);
  }
  else
    return ERR_NO_PRIVILEGE;
  return ERR_OK;
}

int delGroup(int srcID, int groupID)
{
  user u = findUser(srcID);
  if (u.canGroupMg())
    addGroup(groupName, srcID);
  else
    return ERR_NO_PRIVILEGE;

  return ERR_OK;
}

int fetchMemberList(int srcID, int groupID)
{
	if (findUser(srcID).canGroupMg())
	{
		retMemList(findGroup(groupID).groupMember);
		return ERR_OK;
	}
	else
	{
		return ERR_NO_PRIVILEGE;
	}
}

int fetchGroupMsg(int srcID,int groupID,time_t since)
{
	if (findUser(srcID).canGroupMg())
	{
		findGroup(groupID).getMsg(since);
		return ERR_OK;
	}
	else
	{
		return ERR_NO_PRIVILEGE;
	}
}

int fetchGroupList(int srcID)
{
	if (findUser(srcID).canGroupMg())
	{
		std::vector<int> groups;
		std::vector<std::string> names;

		lockGrouplist();
		for (auto it = groupList.begin();it < groupList.end();it++)
		{
			groups.push_back((*it).groupID);
			names.push_back((*it).groupName);
		}
		releaseGrouplist();
		retGroupList(groups,names);
		return ERR_OK;
	}
	else
	{
		return ERR_NO_PRIVILEGE;
	}
}
