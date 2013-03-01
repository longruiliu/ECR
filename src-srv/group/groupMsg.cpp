#include "groupMsg.h"

groupMsg::groupMsg(bool red, int sID, int gID,const std::string& msg)
: msgRecord(sID, gID, msg, MSG_TYPE_GROUP),
isRed(red)
{
}
