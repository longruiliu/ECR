/***********************************************************************
 * Module:  msgRecord.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 3:08:33 PM
 * Purpose: Declaration of the class msgRecord
 ***********************************************************************/

#if !defined(__ServerLogic_msgRecord_h)
#define __ServerLogic_msgRecord_h

#define MSG_TYPE_GROUP		0
#define MSG_TYPE_PERSONAL	1
#define MSG_TYPE_SYSTEM		2
#include<string>
#include<time.h>

class msgRecord
{
public:
	msgRecord(int srcID, int targetID,const std::string& msg, int msgType);
	int srcID;
	int targetID;
	std::string msgText;
	time_t postTime;
	int msgType;
	bool operator < (const msgRecord&); 
	#ifdef DEBUG
	void printMsg() const;
	#endif
};

#endif
