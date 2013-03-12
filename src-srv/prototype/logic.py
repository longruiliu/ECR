import os
import sys

ERR_SESSIONID_EXPECTED, ERR_METHOD_EXPECTED, ERR_TYPE_EXPECTED, ERR_PARAMS_EXPECTED, ERR_INVALID_METHOD, ERR_INVALID_PARAMS, ERR_INVALID_TYPE, ERR_OK, ERR_NOT_IN_GROUP, ERR_NO_PRIVILEGE = range(10)

PRIVILEGE_MASK_GROUPMG = 0x1
PRIVILEGE_MASK_USERMG = 0x2

def sendGroupMsg(srcID, groupID, msg):
    gp = group.findGroup(groupID)
    if gp.isInGroup(srcID):
        gp.postMsg(srcID, msg)
    else:
        return ERR_NOT_IN_GROUP
    return ERR_OK

def sendRedMsg(srcID, groupID, msg):
    gp = group.findGroup(groupID)
    if gp.isInGroup(srcID):
        gp.postRedMsg(srcID, msg)
    else:
        return ERR_NOT_IN_GROUP
    return ERR_OK

def addGroup(srcID, groupName):
    ur = user.findUser(srcID)
    if ur.canGroupMg():
        gid = group.addGroup(groupName, srcID)
        retObj(gid)
        return ERR_OK
    else:
        return ERR_NO_PRIVILEGE

def delGroup(srcID, groupID):
    gp = group.findGroup(groupID)
    if gp.creator == srcID:
        delGroup(groupID)
        return ERR_OK
    else:
        return ERR_NO_PRIVILEGE

