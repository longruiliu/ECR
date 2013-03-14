import json
import socket
from network import SERVER_PORT

test = {'sessionID': 2133462584, 'type': 'regular', 'method': 'add', 'params': [{'type': 'Int', 'value': 1024}]}
test2 = {'type': 'regular', 'method': 'login', 'params': [{'type': 'Int', 'value': -1503}, {'type': 'String', 'value': '123456'}]}

if __name__ == '__main__':
    sock = socket.socket()
    sock.connect(('127.0.0.1', SERVER_PORT))
    o = json.dumps(test)
    sock.send(o)
    print "%s sent" % o
    ret = 1024
    print sock.recv(ret)
    sock.close()
