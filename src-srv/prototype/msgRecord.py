import time

MSG_TYPE_GROUP_REQ = 0
MSG_TYPE_P2P_MSG = 1
MSG_TYPE_UNKNOWN= 2


class MsgRecord(object):
    def __init__(self, sendorID, targetID, msgText):
        self.sendorID = sendorID
        self.targetID = targetID
        self.msgText = msgText
        self.timestamp = time.time()
        self.typeID = MSG_TYPE_UNKNOWN
    def __str__(self):
        return "Msg Dump from %d to %d @ %f:\n%s" %(self.sendorID, self.targetID,self.timestamp, self.msgText)
