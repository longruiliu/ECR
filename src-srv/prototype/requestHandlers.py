from logic import *
requestHandlers = {
    "regular": {
        "login": login,
        "logout":logout,
        "sendmsg":sendMsg,
        "userinfo":getUserInfo,
        "add": addUser,
        "modify":modifyUser,
        "del": delUser,
        "fetchmsg": fetchMsg,
        "keepalive":keepAlive
        },
    "group": {
        "add": addGroup,
        "del": delGroup,
        "sendmsg": sendGroupMsg,
        "joinreq":addGroupMember,
        "quitreq":delGroupMember,
        "userlist": fetchMemberList,
        "redmsg": sendRedMsg,
        "fetchmsg": fetchGroupMsg,
        "fetchgrp" : fetchGroupList
        }
    }
