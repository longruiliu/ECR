import random
userList = {}
#It should be always in mind that all User ID are negative

class User:
    def __init__(self, userID, userName, passwd, userInfo):
        self.userID = userID
        self.userName = userName
        self.passwd = passwd
        self.userInfo = userInfo

def findUser(userID):
    if userID in userList:
        return userList[userID]
    return None

def addUser(userName, passwd, userInfo):
    while True:
        userID = -(random.randint(1,2**13))
        if userID not in userList:
            break
    userList[userID] = User(userID, userName, passwd, userInfo)

def delUser(userID):
    """
    Delete a user pointing by userID
    There will be no hurt when delete a non-exist user
    """
    if userID in userList:
        del userList[userID]

