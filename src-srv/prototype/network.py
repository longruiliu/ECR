import json
import socket
import thread
import pickle
import logic
from logic import ERR_SESSIONID_EXPECTED, ERR_METHOD_EXPECTED, ERR_TYPE_EXPECTED, ERR_PARAMS_EXPECTED, ERR_INVALID_METHOD, ERR_INVALID_PARAMS, ERR_INVALID_TYPE, ERR_OK, ERR_NOT_IN_GROUP, ERR_NO_PRIVILEGE, ERR_WRONG_PASSWD
from session import getUserIDBySession
import unittest_basicData

SERVER_PORT = 0x1024
BACKLOG = 127
sockMapMutex = thread.allocate_lock()
sockMap = {}
MAX_BUFSZ = 4096

def sendNotification(addr, notifyType, extra):
    """
    Async notification conducted by server.
    """
    print "New UDP pack to ", addr, notifyType, extra 
    address = (addr, 0x1024)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto("%x %x"%(notifyType, extra), address)
    s.close()
    

def sendResponse(result):
    final_result = json.dumps(result)
    ident = thread.get_ident()
    sock = sockMap[ident][0]
    sock.send(final_result)

def initialRet(status):
    ret = {}
    ret['status'] = status
    ret['result'] = []
    return ret

# coding it the hard way
def requestHandler(request):
    """
    Call correspond request handler according to the request.
    """
    req_sessionID = request.get("sessioID", None)
    req_type = request.get("type", '')
    req_method = request.get("method", '')
    req_params = request.get("params", [])
    
    
    if req_type == 'regular':
        if req_method == 'login':
            try:
                ident = thread.get_ident()
                ip = sockMap[ident][1]
                params = [item["value"] for item in req_params]
                params.append(ip)
                status, result = apply(logic.login, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret["result"].append({"type": "Int", "value": result})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'logout':
            try:
                status, result = apply(logic.logout, req_sessionID)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'add':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item["value"] for item in req_params].insert(0, srcID)
                status, result = apply(logic.addUser, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret["result"].append({"type": "Int", "value": result})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'del':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.delUser, params)
                ret = initialRet(status)
                
            except:
                pass
        elif req_method == 'modify':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item["value"] for item in req_params].insert(0, srcID)
                status, result = apply(logic.modifyUser, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'sendmsg':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.sendMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'userlist':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.fetchMemberList, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'UserList', 'value': result})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'userinfo':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.getUserInfo, params)
                if status == ERR_OK:
                    ret['result'].append({'type': 'UserInfo', 'value': result})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'keepalive':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.keepAlive, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'fetchmsg':
            try:
                srcID = getUserIDBySession(req_sessionID)
                status, result = apply(logic.keepAlive, srcID)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'MsgList', 'value': [{
                                    'srcID': item.sendorID,
                                    'targetID': item.targetID,
                                    'msgText': item.msgText,
                                    'postTime': item.timestamp,
                                    'msgType': item.typeID}
                                                                       for item in result]})
                sendResponse(ret)
            except:
                pass
        else:
            pass
    elif req_type == 'group':
        if req_method == 'add':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.addGroup, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'Int', 'value': result})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'del':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.delGroup, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'sendmsg':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.sendGroupMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'joinreq':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.addGroupMember, params)
                ret = initialRet(status)
                sendResponse(status)
            except:
                pass
        elif req_method == 'quitreq':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in params].insert(0, srcID)
                status, result = apply(logic.delGroupMember, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'userlist':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in params].insert(0, srcID)
                status, result = apply(logic.fetchMemberList, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'UserList', 'value': [x for x in result]})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'redmsg':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.sendRedMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except:
                pass
        elif req_method == 'fetchmsg':
            try:
                srcID = getUserIDBySession(req_sessionID)
                params = [item['value'] for item in req_params].insert(0, srcID)
                status, result = apply(logic.fetchGroupMsg, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'MsgList', 'value': [{
                                    'srcID': item.sendorID,
                                    'targetID': item.targetID,
                                    'msgText': item.msgText,
                                    'postTime': item.timestamp,
                                    'msgType': item.typeID}
                                                                       for item in result]})
                sendResponse(ret)
            except:
                pass
        elif req_method == 'fetchgrp':
            try:
                srcID = getUserIDBySession(req_sessionID)
                status, result = apply(logic.fetchGroupList, srcID)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'GroupList', 'value': result})
                sendResponse(ret)
            except:
                pass
        else:
            pass
    else:
        pass
        
def recvRoutine(sock, addr):
    """
    When new request arrives, call this routine to respond.
    """
    ident = thread.get_ident()

    sockMapMutex.acquire()
    sockMap[ident] = (sock, addr)
    sockMapMutex.release()
    
    # not very well :(
    recv = sock.recv(MAX_BUFSZ)
    request = json.loads(recv)
    if type(request) is not dict:
        pass

    requestHandler(request)
    sockMapMutex.acquire()
    sockMap.pop(ident)
    sockMapMutex.release()
    sock.close()

def main():
    sock = socket.socket()
    sock.bind(('0.0.0.0', SERVER_PORT))
    sock.listen(BACKLOG)
    while (1):
        newsock, addr = sock.accept()
        thread.start_new_thread(recvRoutine, (newsock, addr))
    
if __name__ == '__main__':
    main()
