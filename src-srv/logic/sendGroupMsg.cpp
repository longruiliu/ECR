#include "proto.h"
#include "group/groupMsg.h"
#include <string>

using namespace std;

int sendGroupMsg(int sessionID, int groupID, const string& msg)
{
	struct sendMsgAg* v = (struct sendMsgAg*) argv;
	if (dstID > 0)
		return ERR_INVAILD;
	else
	{
		group g = mainGM.findGroup(dstID);
		if (g.isInGroup(srcID))
		{	
			g.postMsg(dstID, msg);
			return ERR_OK;
		}
		else
			return ERR_NOT_IN_GROUP;
	}
}

int sendRegMsg(int sessionID

