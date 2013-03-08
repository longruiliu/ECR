#include "msgRecord.h"
#include <time.h>

msgRecord::msgRecord(int sID, int tID, const std::string& msg, int type):
srcID(sID), targetID(tID), msgText(msg), msgType(type)
{
	postTime = time(NULL);
}

bool msgRecord::operator < (const msgRecord& to)
{
	return postTime < to.postTime;
}

#ifdef DEBUG
#include<iostream>
void msgRecord::printMsg() const
{
	std::cout << msgType << ":" << msgText << std::endl;
}
#endif
