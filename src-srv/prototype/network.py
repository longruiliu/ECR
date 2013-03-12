import json
import socket
import thread

SERVER_PORT = 2333
BACKLOG = 127

def responseHandler(method, args):
    """
    Call correspond response handler to respond.
    """
    return apply(responseHandlers[method], args)

def requestHandler(**request):
    """
    Call correspond request handler according to the request.
    """
    
    if not request.has_key("type"):
        return ERR_TYPE_EXPECTED
    if not request.has_key("method"):
        return ERR_METHOD_EXPECTED
    
    req_type = request["type"]
    if req_type == "regular":
        pass
    elif req_type == "group":
        pass
    else:
        return ERR_INVALID_TYPE
    
def recvRoutine(sock, addr):
    """
    When new request arrives, call this routine to respond.
    """
    recv = sock.recv()
    request = json.load(recv)
    if type(request) is not dict:
        return ERR_INVALID_REQUEST
    return requestHandler(request)

def main():
    sock = socket.socket()
    sock.bind(('localhost', SERVER_PORT))
    sock.listen(BACKLOG)
    while (1):
        newsock, addr = sock.accept()
        thread.start_new_thread(recvRoutine, newsock, addr)
    
if __name__ == '__main__':
    main()
