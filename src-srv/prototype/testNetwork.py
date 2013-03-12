import json
import random
import socket
from network import SERVER_PORT

test = {'sessionID': 1024, 'type': 'regular', 'method': 'add', 'params': [1024]}

if __name__ == '__main__':
    sock = socket.socket()
    sock.connect(('localhost', SERVER_PORT))
    o = json.dumps(test)
    sock.send(o)
    print "%s sent" % o
    ret = 1024
    print sock.recv(ret)
    sock.close()
