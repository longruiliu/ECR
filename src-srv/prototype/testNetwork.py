import json
import socket
SERVER_PORT = 2054

test = {'sessionID': 1024, 'type': 'regular', 'method': 'add', 'params': [1024]}
test2 = {'type': 'regular', 'method': 'login', 'params': [-6577, '123456']}

if __name__ == '__main__':
    sock = socket.socket()
    sock.connect(('127.0.0.1', SERVER_PORT))
    o = json.dumps(test2)
    sock.send(o)
    print "%s sent" % o
    ret = 1024
    print sock.recv(ret)
    sock.close()
