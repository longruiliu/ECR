import unittest_basicData
import logic

print "Unittest Logic"
rootID = unittest_basicData.uid
st, lzsID = logic.addUser(rootID, "lzs", "123", "rr")
st, xhjID = logic.addUser(rootID, "xhj", "123", "rr")
print logic.modifyUser(rootID, lzsID, "lzs","124", 0x7 , "ff")
print logic.getUserInfo(rootID, lzsID)
st, groupID = logic.addGroup(lzsID, "ECR")
print "groupID:" , groupID
print logic.addGroupMember(lzsID, groupID, xhjID, "rv")
print logic.fetchMemberList(xhjID,groupID)
print logic.fetchMemberList(lzsID,groupID)
st, sessionID = logic.login(lzsID, "124", 213)
print st, sessionID
print logic.logout(sessionID)


print logic.sendGroupMsg(xhjID, groupID, "aha aha ho")
for i in logic.fetchGroupMsg(lzsID, groupID, 0)[1]:
    print i
