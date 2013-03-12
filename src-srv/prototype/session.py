import random
import time
KAI = 4 #Keep-alive interval
sessionList_uk = {} 
sessionList_sk = {}

def renewUser(userID):
    sessionList_uk[userID] = sessionList_uk[userID][:-1]+(time.time(),)

def cleanDeadUser():
    deadline = time.time() - KAI
    for u,v in sessionList_uk.items():
        if v[2] < deadline:
            deregisterSession(v[0])

def registerSession(userID, IP):
    if userID in sessionList_uk:
        sessionID = sessionList_uk[userID][0]
        deregisterSession(sessionID)
    while True:
        sessionID = random.randint(0, 2**31)
        if not (sessionID in sessionList_sk):
            break
    sessionList_sk[sessionID] = userID
    sessionList_uk[userID] = (sessionID, IP, time.time())
    return sessionID
    

def getUserIDBySession(sessionID):
    if sessionID in sessionList_sk:
        return sessionList_sk[sessionID]
    return None

def deregisterSession(sessionID):
    uID = sessionList_sk[sessionID]
    del sessionList_sk[sessionID]
    del sessionList_uk[uID]
