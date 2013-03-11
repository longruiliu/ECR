import time
class MsgRecord(object):
    def __init__(self, sendorID, targetID, msgText):
        self.sendorID = sendorID
        self.targetID = targetID
        self.msgText = msgText
        self.timestamp = time.time()
    def __str__(self):
        return "Msg Dump from %d to %d:\n%s" %(sendorID, targetID, msgText)
