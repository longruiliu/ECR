import logic
import json
import socket
import thread

SERVER_PORT = 2333
BACKLOG = 127

def routine(sock, addr):
    recv = sock.recv()
    result = json.load(recv)
    if type(result) is not dict:
        pass
    

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
