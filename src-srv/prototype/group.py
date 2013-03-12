import random
import user
import msgRecord
groupList = {}

def findGroup(groupID):
    """
    Find a group object out by groupID
    """
    return groupList[groupID]

def addGroup(groupName, creator):
    """
    Add a group called groupName. Specify it belong to creator
    Return the groupID
    """
    tmp = Group(groupName, creator)
    while True:
        groupID = random.randint(1, 2**13)
        if groupID not in groupList:
            break
    tmp.groupID = groupID
    tmp.addMember(creator)
    groupList[groupID] = tmp
    return groupID

def delGroup(groupID):
    """
    Delete a group
    NO PRIVILEGE CHECK HERE!!
    So make sure it can be done first
    You can delete a non-exist grouop and there would be no trouble
    """
    if groupID in groupList:
        del groupList[groupID]

class Group():
    def __init__(self, groupName, creator):
        self.msgList = []
        self.groupMember = {}
        self.creator = creator
        self.groupID = 0
        self.groupName = groupName
    def getMsg(self, time):
        """
        Get Message from a specific time
        If it's not in memory, it gonna be a while to get it out from database
        """
        a = -1
        for (i,p) in enumerate(self.msgList):
            if time < p.timestamp:
                a = i
                break
        return self.msgList[a:]
    def postMsg(self, srcID, msg):
        """
        Post a message to the group
        """
        self.msgList.append(GroupMsg(srcID, self.groupID, False, msg))
    def postRedMsg(self, srcID, msg):
        """
        Post a message to the group
        """
        self.msgList.append(GroupMsg(srcID, self.groupID, True, msg))
    
    def isInGroup(self, userID):
        """
        Find out if a user is in this group
        """
        return (userID in self.groupMember)

    def addMember(self, userID):
        """
        Add a user into this group
        Add a non-exist user will have no result and no trouble
        """
        u = user.findUser(userID)
        if u != None:
            self.groupMember[userID] = u

    def delMember(self, userID):
        """
        Delete a user from this group
        You can delete a non-exist user and there would be no trouble
        """
        if userID in self.groupMember:
            del self.groupMember[userID]

class GroupMsg(msgRecord.MsgRecord):
    def __init__(self, sendorID, targetID, isRed, msgText):
        super(GroupMsg, self).__init__(sendorID, targetID, msgText)
        self.isRed = isRed
    def __str__(self):
        if self.isRed:
            output = 'This is a red groupMsg\n'
        else:
            output = 'This is a groupMsg\n'
        output += super(GroupMsg, self).__str__()
        return output
