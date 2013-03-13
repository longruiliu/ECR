/***********************************************************************
 * Module:  groupMsg.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:05:09 PM
 * Purpose: Declaration of the class groupMsg
 ***********************************************************************/

#if !defined(__ServerLogic_groupMsg_h)
#define __ServerLogic_groupMsg_h

#include "../msgRecord.h"

class groupMsg : public msgRecord
{
public:
	groupMsg(bool isRed, int srcID, int groupID,const std::string& msg);
protected:
private:
   int isRed;
};

#endif
