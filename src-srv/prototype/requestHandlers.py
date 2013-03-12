from user import *
from group import *

groupHandlers = {
    "add": addGroup,
    "del": delGroup,
    "adduser": addGroupMember,
    "deluser": delGroupMember,
    "userlist": fetchMemberList,
    "redmsg": sendResMsg
    }

regularHandlers = {
    "login": login,
    "logout": logout,
    "sendmsg": sendMsg,
    "userinfo": getUserInfo,
    "add": addUser,
    "modify": modifyUser,
    "del": delUser,
    "fetch": fetchMsg
    }
