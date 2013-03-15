import json

def login(uid, pw):
    req = {}
    req['type'] = 'regular'
    req['method'] = 'login'
    req['params'] = [{'type': 'Int', 'value': uid},
                     {'type': 'String', 'value': pw}]
    stat, result = requestAgent(req)
    if stat == ERR_OK:
        sessionID = 

def logout():
    req = {}
    req['type'] = 'regular'
    req['method'] = 'logout'
    req['params'] = []
    stat, result = requestAgent(req)

def addUser():
    req = {}
    
def delUser():
    req = 
