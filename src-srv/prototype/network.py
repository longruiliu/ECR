import json
import socket
import thread
import mutex
import pickle
from logic import *
from session import *
from requestHandlers import requestHandlers
import unittest_basicData

SERVER_PORT = 0x1024
BACKLOG = 127
sockMapMutex = mutex.mutex()
sockMap = {}

def checkParams(req_type, req_method, req_params):
    """
    Deprecated function.
    """
    params = requestHandlers[req_type][req_method]["args"]
    ret = []
    if len(params) != req_params:
        return None
    for i in xrange(len(params)):
        if type(req_params[i]) is not params[i]:
            try:
                req_params[i] = params[i](req_params[i])
            except:
                try:
                    proto = (params[i])()
                    if (req_params[i].keys() != proto.__dict__.keys()):
                        return None
                    else:
                        for k in req_params[i].keys():
                            proto.__dict__[k] = req_params[i][k]
                        req_params[i] = proto
                except:
                    return None
    return req_params
    
def sendResponse(result):
    """
    When finished serializing the objects, call this function to send result.
    """

    try:
        ret = json.dumps(result)
    except:
        # for current protocol, it occurs when met with group message list
        ret = []
        for i in xrange(len(result)):
            gmr = result[i]
            temp = {}
            for k in gmp.__dict__.keys():
                temp[k] = gmr.__dict__[k]
            ret.append(temp)
        ret = json.dumps(ret)
        
    # release thread/socket binding
    ident = thread.get_ident()
    sock = sockMap[ident][0]
    sock.send(ret)
    return ERR_OK
    
def sendNotification(addr, notifyType, extra):
    """
    Async notification conducted by server.
    """
    print "New UDP pack to ", addr, notifyType, extra 
    address = (addr, 0x1024)
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    s.sendto("%x %x"%(notifyType, extra), address)
    
def responseHandler(method, args):
    """
    Call correspond response handler to respond.
    """
    return apply(responseHandlers[method], args)

def paramsFormalizer(request):
    req_type = request["type"]
    req_method = request["method"]
    params = request["params"][:]

    if req_method == 'login':
        ident = thread.get_ident()
        ip = sockMap[ident][1]
        params.append(ip)
    elif req_method == 'logout':
        params.append(request["sessionID"])
    else:
        srcID = getUserIDBySession(request["sessionID"])
        params.insert(0, srcID)
    return params

def requestHandler(request):
    """
    Call correspond request handler according to the request.
    """
    
    if not request.has_key("type"):
        return ERR_TYPE_EXPECTED
    if not request.has_key("method"):
        return ERR_METHOD_EXPECTED
    if not request.has_key("params"):
        return ERR_PARAMS_EXPECTED

    req_type = request["type"]
    req_method = request["method"]
    req_params = request["params"]

    method = requestHandlers[req_type][req_method]
    params = paramsFormalizer(request)

    if params == None:
        return ERR_INVALID_PARAMS

    try:
        status, result = apply(method, params)
    except:
        return ERR_INVALID_PARAMS

    if status != ERR_OK:
        return status
    elif result != None:
        return sendResponse(result)
    return ERR_OK

def addToSockMap(args):
    sockMap[args[0]] = (args[1], args[2])

def rmFromSockMap(ident):
    sockMap.pop(ident)

def recvRoutine(sock, addr):
    """
    When new request arrives, call this routine to respond.
    """
    ident = thread.get_ident()

    sockMapMutex.lock(addToSockMap, (ident, sock, addr))
    sockMapMutex.unlock()
    
    # not very well :(
    recv = sock.recv(1024)
    request = json.loads(recv)
    if type(request) is not dict:
        return ERR_INVALID_REQUEST
    requestHandler(request)

    sockMapMutex.lock(rmFromSockMap, ident)
    sockMapMutex.unlock()
    sock.close()

def main():
    sock = socket.socket()
    sock.bind(('0.0.0.0', SERVER_PORT))
    sock.listen(BACKLOG)
    while (1):
        newsock, addr = sock.accept()
        recvRoutine(newsock, addr)
    
if __name__ == '__main__':
    main()
