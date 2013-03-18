import simplejson as json
import struct
import socket
import thread
import pickle
import logic,time
import sys

from logic import ERR_SESSIONID_EXPECTED, ERR_METHOD_EXPECTED, ERR_TYPE_EXPECTED, ERR_PARAMS_EXPECTED, ERR_INVALID_METHOD, ERR_INVALID_PARAMS, ERR_INVALID_TYPE, ERR_OK, ERR_NOT_IN_GROUP, ERR_NO_PRIVILEGE, ERR_WRONG_PASSWD, ERR_INVALID_REQUEST

from session import getUserIDBySession

SERVER_PORT = 0x1024
BACKLOG = 127
sockMapMutex = thread.allocate_lock()
requestMutex = thread.allocate_lock()
sockMap = {}
MAX_BUFSZ = 16*2**20


def checkSessionID(req_sessionID):
    try:
        srcID = getUserIDBySession(req_sessionID)
        if srcID == None or srcID < 0:
            fatal("Invalid sessionID")
    except Exception, e:
        print e
        fatal(e)
    return srcID

def sendNotification(addr, notifyType, extra):
    """
    Async notification conducted by server.
    """
    print "New UDP pack to ", addr, notifyType, extra 
    address = (addr, 0x1024)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto(struct.pack("ii", notifyType, extra), address)
    s.close()

def fatal(error):
    print error
    ident = thread.get_ident()
    sock = sockMap[ident][0]
    sock.send(json.dumps({'status': ERR_INVALID_REQUEST, 'result': []}))

    sockMapMutex.acquire()
    sockMap.pop(ident)
    sockMapMutex.release()

    sock.close()
    requestMutex.release()
    thread.exit()
    
def sendResponse(result):
    #print "before encap %s" % result
    final_result = json.dumps(result,encoding="utf8")
    #print "after encap %s" % final_result
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
    req_sessionID = request.get("sessionID", None)
    req_type = request.get("type", '')
    req_method = request.get("method", '')
    req_params = request.get("params", [])
    
    
    if req_type == 'regular':
        if req_method == 'login':
            try:
                ident = thread.get_ident()
                ip = sockMap[ident][1][0]
                params = [item["value"] for item in req_params]
                params.append(ip)
                print params
                status, result = apply(logic.login, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret["result"].append({"type": "Int", "value": result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)

        elif req_method == 'logout':
            try:
                status, result = apply(logic.logout, [req_sessionID])
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)

        elif req_method == 'add':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.addUser, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret["result"].append({"type": "Int", "value": result})
                sendResponse(ret)
            except Exception, e:
                  fatal(e)

        elif req_method == 'del':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.delUser, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)

        elif req_method == 'modify':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.modifyUser, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'sendmsg':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.sendMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)

        elif req_method == 'userlist':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.fetchUserList, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'UserList', 'value': result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)

        elif req_method == 'userinfo':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.getUserInfo, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'Dict', 'value': result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'keepalive':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.keepAlive, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'fetchmsg':
            try:
                srcID = checkSessionID(req_sessionID)
                status, result = apply(logic.fetchMsg, [srcID])
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
                logic.postFetchMsg(srcID)
            except Exception, e:
                fatal(e)
        else:
            fatal('method not defined')
    elif req_type == 'group':
        if req_method == 'add':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.addGroup, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'Int', 'value': result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'del':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.delGroup, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'sendmsg':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.sendGroupMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'joinreq':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.addGroupMember, params)
                ret = initialRet(status)
                sendResponse(status)
            except Exception, e:
                fatal(e)
        elif req_method == 'quitreq':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.delGroupMember, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'userlist':
            try:
                srcID = checkSessionID(req_sessionID)
                print req_params
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.fetchMemberList, params)
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'UserList', 'value': result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'redmsg':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
                status, result = apply(logic.sendRedMsg, params)
                ret = initialRet(status)
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        elif req_method == 'fetchmsg':
            try:
                srcID = checkSessionID(req_sessionID)
                params = [srcID] + [item['value'] for item in req_params]
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
            except Exception, e:
                fatal(e)
        elif req_method == 'fetchgrp':
            try:
                srcID = checkSessionID(req_sessionID)
                status, result = apply(logic.fetchGroupList, [srcID])
                ret = initialRet(status)
                if status == ERR_OK:
                    ret['result'].append({'type': 'GroupList', 'value': result})
                sendResponse(ret)
            except Exception, e:
                fatal(e)
        else:
            fatal("method not defined")
    else:
        fatal("request type not defined")
        
def recvRoutine(sock, addr):
    """
    When new request arrives, call this routine to respond.
    """
    ident = thread.get_ident()

    sockMapMutex.acquire()
    sockMap[ident] = (sock, addr)
    sockMapMutex.release()
    
    # not very well :(
    

    total_data=[]
    while True:
        data = sock.recv(8192)
        if not data: break
        total_data.append(data)
        print len(data)
    recv =  ''.join(total_data)
    print len(recv)
    #print recv
    try:
        recv = recv.decode("utf8")
        request = json.loads(recv)
    except Exception, e: fatal(e)

    if type(request) is not dict:
        fatal("request might not be valid")

    requestMutex.acquire()
    requestHandler(request)
    requestMutex.release()
    
    sockMapMutex.acquire()
    sockMap.pop(ident)
    sockMapMutex.release()
    sock.close()

def recv_timeout(the_socket,timeout=2):
    the_socket.setblocking(0)
    total_data=[];data='';begin=time.time()
    while 1:
        #if you got some data, then break after wait sec
        if total_data and time.time()-begin>timeout:
            break
        #if you got no data at all, wait a little longer
        elif time.time()-begin>timeout*2:
            break
        try:
            data=the_socket.recv(8192)
            if data:
                total_data.append(data)
                begin=time.time()
            else:
                time.sleep(0.1)
        except:
            pass
    return ''.join(total_data)

def main():
    sock = socket.socket()
    sock.bind(('0.0.0.0', SERVER_PORT))
    sock.listen(BACKLOG)
    try:
        while (1):
            newsock, addr = sock.accept()
            print "some one connect"
            thread.start_new_thread(recvRoutine, (newsock, addr))
    except Exception, e:
        print e
        sock.close()
        sys.exit()
    
if __name__ == '__main__':
    main()
