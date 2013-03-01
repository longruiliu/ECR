#include "proto.h"
#include "group/groupMsg.h"
#include <string>

using namespace std;

int ecrPH_sendMsg(int srcID, int dstID, const string& msg)
{
	struct sendMsgAg* v = (struct sendMsgAg*) argv;
	if (dstID > 0)
		return ERRNO_INVAILD;
	else
	{
		group g = mainGM.findGroup(dstID);
		if (g.isInGroup(srcID))
		{	
			g.postMsg(dstID, msg);
			return ERRNO_OK;
		}
		else
			return ERRNO_NOTINGROUP;
	}
}
