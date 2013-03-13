import os
import session
import sys
import user
import group

ERR_SESSIONID_EXPECTED, ERR_METHOD_EXPECTED, ERR_TYPE_EXPECTED, ERR_PARAMS_EXPECTED, ERR_INVALID_METHOD, ERR_INVALID_PARAMS, ERR_INVALID_TYPE, ERR_OK, ERR_NOT_IN_GROUP, ERR_NO_PRIVILEGE, ERR_WRONG_PASSWD= range(11)

PRIVILEGE_MASK_GROUPMG = 0x1
PRIVILEGE_MASK_USERMG = 0x2
PRIVILEGE_MASK_ROOT = 0x4

def sendGroupMsg(srcID, groupID, msg):
    gp = group.findGroup(groupID)
    if gp.isInGroup(srcID):
        gp.postMsg(srcID, msg)
        for i in gp.groupMember.keys():
            IP = getUserID(i) 
            if IP != -1:
                network.sendNotification(IP, msgRecord.NOTIFY_GROUP_MSG, groupID)
    else:
        return (ERR_NOT_IN_GROUP,None)
    return (ERR_OK,None)

def sendRedMsg(srcID, groupID, msg):
    gp = group.findGroup(groupID)
    if gp.isInGroup(srcID):
        gp.postRedMsg(srcID, msg)
        return (ERR_OK,None)
    else:
        return (ERR_NOT_IN_GROUP,None)

def addGroup(srcID, groupName):
    ur = user.findUser(srcID)
    if ur.canGroupMg():
        gid = group.addGroup(groupName, srcID)
        return (ERR_OK,gid)
    else:
        return (ERR_NO_PRIVILEGE,None)

def delGroup(srcID, groupID):
    gp = group.findGroup(groupID)
    if gp.creator == srcID:
        delGroup(groupID)
        return (ERR_OK,None)
    else:
        return (ERR_NO_PRIVILEGE,None)

def addGroupMember(srcID, groupID, newMemberID, msg):
    gp = group.findGroup(groupID)
    if gp.creator == srcID:
        gp.addMember(newMemberID)
        ur = user.findUser(gp.srcID)
        ur.sendMsg(msgRecord.MsgRecord(0, srcID, "Join Group Req Granted:%d" %(groupID,), msgRecord.MSG_GROUP_REQ_GRAND))
        return (ERR_OK, None)
    else:
        ur = user.findUser(gp.creator)
        ur.sendMsg(msgRecord.MsgRecord(0, gp.creator, "Join Group Req:%d %d" %(srcID, groupID), msgRecord.MSG_JOIN_GROUP_REQ))
        return (ERR_OK,None)

def delGroupMember(srcID, groupID, memberID):
    gp = group.findGroup(groupID)
    if (srcID == memberID):
        gp.delMember(srcID)
    elif (srcID == gp.creator):
        gp.delMember(memberID)
    else:
        return (ERR_NO_PRIVILEGE, None)
    return (ERR_OK, None)

def fetchMemberList(srcID, groupID):
    gp = group.findGroup(groupID)
    if gp.isInGroup(srcID):
        return (ERR_OK, gp.groupMember)
    else:
        return (ERR_NOT_IN_GROUP, None)

def fetchGroupMsg(srcID, groupID, since):
    gp = group.findGroup(groupID)
    if (gp.isInGroup(srcID)):
        return (ERR_OK, gp.getMsg(since))
    else:
        return (ERR_NOT_IN_GROUP, None)

def fetchGroupList(srcID):
    gpL = []
    for i in group.groupList:
        if i.isInGroup(srcID):
            gpL.append((i.groupID, i.groupName))
    return (ERR_OK, gpL)

def login(userID, passwd, IP):
    ur = user.findUser(userID)
    print passwd, ur.passwd, ur.passwd == passwd
    if ur != None and ur.passwd == passwd:
        return (ERR_OK, session.registerSession(userID, IP))
    else:
        return (ERR_WRONG_PASSWD,None)

def logout(sessionID):
    session.deregisterSession(sessionID)
    return (ERR_OK,None)

def getUserInfo(srcID, dstID):
    ur = user.findUser(dstID)
    return (ERR_OK, {'userName':ur.userName, 'userInfo':ur.userInfo})

def addUser(srcID, userName, passwd, userInfo):
    ur = user.findUser(srcID)
    if (ur.canUserMg()):
        return (ERR_OK, user.addUser(userName, passwd, userInfo))
    else:
        return (ERR_NO_PRIVILEGE, None)

def modifyUser(srcID, userID, newName, newPasswd, newPriv, newInfo):
    srcUr = user.findUser(srcID)
    if (not newPriv==-1) and (not srcUr.isRoot()):
        return (ERR_NO_PRIVILEGE, None)
    if (srcUr.canUserMg() or srcID == userID):
        ur = user.findUser(userID)
        ur.userName = newName
        ur.passwd = newPasswd
        ur.userInfo = newInfo
        if not newPriv==-1:
            ur.privMask = newPriv
        return (ERR_OK, None)
    else:
        return (ERR_NO_PRIVILEGE, None)

def delUser(srcID, userID):
    ur = user.findUser(srcID)
    if ur.canUserMg():
        user.delUser(userID)

def sendMsg(srcID, dstID, msg):
    dstUr = user.findUser(dstID)
    if not dstUr == None:
        newMsg = msgRecord.MsgRecord(srcID, dstID, msg)
        newMsg.typeID = msgRecord.MSG_TYPE_P2P_MSG
        dstUr.sendMsg(newMsg)
        return (ERR_OK, None)
    else:
        return (ERR_NO_PRIVILEGE, None)

def fetchMsg(srcID):
    return (ERR_OK, user.findUser(srcID).fetchMsg())

def postFetchMsg(srcID):
    user.findUser(srcID).mailbox = []

def keepAlive(srcID):
    return (ERR_OK, renewUser(srcID))
