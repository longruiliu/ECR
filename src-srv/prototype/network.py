import json
import socket
import thread

SERVER_PORT = 2333
BACKLOG = 127

def responseHandler(method, args):
    apply(responseHandlers[method], args)
    
def requestHander(**request):
    if not request.has_key("type"):
        return ERR_TYPE_EXPECTED
    req_type = request["type"]
    if req_type == "regular":
        pass
    elif req_type == "group":
        pass
    else:
        return ERR_INVALID_TYPE
        
def recvRoutine(sock, addr):
    recv = sock.recv()
    request = json.load(recv)
    if type(request) is not dict:
        return ERR_INVALID_REQUEST
    requestHandler(request)

def main():
     sock = socket.socket()
     sock.bind((0, SERVER_PORT))
     sock.listen(BACKLOG)
     while (1):
         newsock, addr = sockt.accpet()
         # thread handler
         thread.start_new_thread(routine, (newsock, addr))
    
if __name__ == '__main__':
    main()
