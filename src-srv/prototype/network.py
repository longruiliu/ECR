import json
import socket
import thread
import mutex
import pickle
import logic
import session
from requestHandlers import requestHandlers


SERVER_PORT = 2333
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
    
def sendResponse():
    """
    When finished serializing the objects, call this function to send result.
    """
    
    # release thread/socket binding
    ident = thread.get_ident()
    sockMapMutex.lock()
    sockMap.pop(ident)
    sockMapMutex.unlock()
    
def sendNotification(addr, msg):
    """
    Async notification conducted by server.
    """
    
def responseHandler(method, args):
    """
    Call correspond response handler to respond.
    """
    return apply(responseHandlers[method], args)

def paramsFormalizer(**request):
    req_type = request["type"]
    req_method = request["method"]
    params = request["params"][:]

    if req_method != 'login':
        srcID = getUserIDBySession(request["sessionID"])
        params.insert(0, srcID)
    else:
        ident = thread.get_ident()
        ip = sockMap[ident][1]
        params.append(ip)
    return params

def requestHandler(**request):
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

    return apply(method, params)

def recvRoutine(sock, addr):
    """
    When new request arrives, call this routine to respond.
    """
    ident = thread.get_ident()

    sockMapMutex.lock()
    sockMap[ident] = (sock, addr)
    sockMapMutex.unlock()

    recv = sock.recv()
    request = json.load(recv)
    if type(request) is not dict:
        return ERR_INVALID_REQUEST
    requestHandler(request)

def main():
    sock = socket.socket()
    sock.bind(('localhost', SERVER_PORT))
    sock.listen(BACKLOG)
    while (1):
        newsock, addr = sock.accept()
        thread.start_new_thread(recvRoutine, newsock, addr)
    
if __name__ == '__main__':
    main()
