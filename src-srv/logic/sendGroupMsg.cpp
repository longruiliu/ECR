#include "proto.h"
#include "group/groupMsg.h"
#include <string>

using namespace std;

int sendGroupMsg(int srcID, int groupID, const string& msg)
{
	if (dstID < 0)
		return ERR_INVAILD;
	else
	{
		group g = findGroup(dstID);
		if (g.isInGroup(srcID))
		{	
			g.postMsg(dstID, msg);
			return ERR_OK;
		}
		else
			return ERR_NOT_IN_GROUP;
	}
}

int sendRegMsg(int srcID, int groupID, const string& msg)
{
  string tmp = string("<div style='color:red'>") + msg + string("</div>"); 
  sendGroupMsg(src, groupID, msg);
}

