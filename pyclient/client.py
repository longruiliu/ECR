import json

sessionID = 0

def login(uid, pw):
    req = {}
    req['type'] = 'regular'
    req['method'] = 'login'
    req['params'] = [{'type': 'Int', 'value': uid},
                     {'type': 'String', 'value': pw}]
    stat, result = requestAgent(req)
    if stat == ERR_OK:
        sessionID = result['value']

def logout():
    req = {}
    req['type'] = 'regular'
    req['method'] = 'logout'
    req['params'] = []
    stat, result = requestAgent(req)

def addUser(
    req = {}
    req['sessionID'] = sessionID
    req['type'] = 'regular'
    req['method'] = 'add'
    req['params'] = [{'type': 'String', 'value': 'eiL'},
                     {'type': 'String', 'value

def delUser():
    req = 
