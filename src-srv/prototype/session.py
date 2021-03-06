import random
import time
import thread
KAI = 3600 #Keep-alive interval
sessionList_uk = {} 
sessionList_sk = {}

def renewUser(userID):
    if sessionList_uk.has_key(userID):
        sessionList_uk[userID] = sessionList_uk[userID][:-1]+(time.time(),)		

def cleanDeadUser():
    deadline = time.time() - KAI
    for u,v in sessionList_uk.items():
        if v[2] < deadline:
            deregisterSession(v[0])

def registerSession(userID, IP):
    if sessionList_uk.has_key(userID):
        sessionID = sessionList_uk[userID][0]
        deregisterSession(sessionID)
    while True:
        sessionID = random.randint(0, 2**31)
        if not (sessionList_sk.has_key(sessionID)):
            break
    sessionList_sk[sessionID] = userID
    sessionList_uk[userID] = (sessionID, IP, time.time())
    return sessionID
    
def getUserIP(userID):
    if sessionList_uk.has_key(userID):
        return sessionList_uk[userID][1]
    else:
        return -1

def getUserIDBySession(sessionID):
    if sessionList_sk.has_key(sessionID):
        return sessionList_sk[sessionID]
    return None

def deregisterSession(sessionID):
    if not sessionList_sk.has_key(sessionID):
        return
    uID = sessionList_sk[sessionID]
    del sessionList_sk[sessionID]
    del sessionList_uk[uID]
