import random
import logic
import group
import session
userList = {}
#It should be always in mind that all User ID are negative

class User(object):
    def __init__(self, userID, userName, passwd, userInfo, privMask = 0):
        self.userID = userID
        self.userName = userName
        self.passwd = passwd
        self.userInfo = userInfo
        self.privMask = privMask
        self.mailbox = []
        self.groupList = []
        self.groupListIsNew = False
    def canGroupMg(self):
        return self.checkPriv(logic.PRIVILEGE_MASK_GROUPMG)
    def canUserMg(self):
        return self.checkPriv(logic.PRIVILEGE_MASK_USERMG)
    def isRoot(self):
        return self.checkPriv(logic.PRIVILEGE_MASK_ROOT)
    def checkPriv(self, mask):
        return not ((self.privMask & mask) == 0)
    def sendMsg(self,msg):
        self.mailbox.append(msg)
        IP = session.getUserIP(self.userID)
        if IP!=-1:
            network.sendNotification(IP, msgRecord.NOTIFY_P2P_MSG, msg.typeID)
    def fetchMsg(self):
        return self.mailbox[:]
    def fetchGroupList(self):
        if not self.groupListIsNew:
            self.groupList = []
            for i in group.groupList.values():
                if i.isInGroup(self.userID):
                    self.groupList.append((i.groupID, i.groupName))
            self.groupListIsNew = True
        return self.groupList

def findUser(userID):
    if userID in userList:
        return userList[userID]
    return None

def addUser(userName, passwd, userInfo):
    while True:
        userID = (random.randint(1,2**13))
        if userID not in userList:
            break
    userList[userID] = User(userID, userName, passwd, userInfo)
    return userID

def delUser(userID):
    """
    Delete a user pointing by userID
    There will be no hurt when delete a non-exist user
    """
    if userID in userList:
        del userList[userID]

