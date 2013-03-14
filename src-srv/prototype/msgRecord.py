import time

MSG_TYPE_GROUP_MSG = 0
MSG_TYPE_GROUP_RED = 1
MSG_TYPE_P2P_MSG = 2
MSG_TYPE_UNKNOWN= 3
MSG_JOIN_GROUP_REQ = 4
MSG_GROUP_REQ_GRANT = 5

NOTIFY_GROUP_MSG = 0
NOTIFY_P2P_MSG = 1

class MsgRecord(object):
    def __init__(self, sendorID, targetID, msgText, typeID = MSG_TYPE_UNKNOWN):
        self.sendorID = sendorID
        self.targetID = targetID
        self.msgText = msgText
        self.timestamp = time.time()
        self.typeID = typeID
    def __str__(self):
        return "Msg Dump from %d to %d @ %f:\n%s" %(self.sendorID, self.targetID,self.timestamp, self.msgText)
