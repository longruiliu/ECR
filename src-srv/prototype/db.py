import sqlite3
import user
import group
import msgRecord
import time

solo_run = 0

def restoreFromDB(dbFileName, timeL):
    """
    Read data from database illustrated by dbFileName
    timeL specify the how old message you want get out of database
    every message from now - timeL to now while be restore
    """
    conn = sqlite3.connect(dbFileName)
    c = conn.cursor()
    results = c.execute("select * from User")
    for result in results:
        tmp = user.User(result[0],result[1],result[2],result[4],result[3])
        user.userList[tmp.userID] = tmp
        print "New user %d: %s" % (tmp.userID ,tmp.userName)

    results = c.execute("select * from Group_list")
    for result in results:
        tmp = group.Group(result[2],result[1])
        tmp.groupID = result[0]
        group.groupList[tmp.groupID] = tmp
        print "New group %d: %s" % (tmp.groupID, tmp.groupName)

    results = c.execute("select user_id,group_id from User_Group")
    for result in results:
        g = group.findGroup(result[1])
        u = user.findUser(result[0])
        g.groupMember[u.userID] = u

    results = c.execute("select * from Message where send_time > ?",(timeL,))
    for result in results:
        g = group.findGroup(result[1])
        tmp = msgRecord.MsgRecord(result[2],result[1],result[5],result[4])
        tmp.timestamp = int(result[3])
        g.msgList.append(tmp)

    conn.commit()
    conn.close()	


def saveToDB(dbFileName):
    """
    Save memory data into database
    """
    global solo_run
    if solo_run == 1:
        return
    
    sqlite3.register_adapter(group.GroupMsg, groupMsgAdapter)
    sqlite3.register_adapter(group.Group, groupAdapter)
    sqlite3.register_adapter(user.User, userAdapter)
    conn = sqlite3.connect(dbFileName)
    c = conn.cursor()
    c.execute("delete  from User")
    c.executemany("insert into User(user_id, u_name, pwd, previlege, info) values(?,?,?,?,?)", userAdapter(user.userList.values()))

    c.execute("delete  from Group_list")
    c.executemany("insert into Group_list(group_id, creator_id, g_name) values(?,?,?)", groupAdapter(group.groupList.values()))

    c.execute("delete  from User_Group")
    for v in group.groupList.values():
        c.executemany("insert into User_Group(user_id, group_id) values(?, ?)", [(r, v.groupID) for r in v.groupMember.keys()])

    c.execute("delete from Message")
    for gp in group.groupList.values():
    	c.executemany("insert into Message(group_id, user_id, send_time, m_type, content) values(?,?,?,?,?)", groupMsgAdapter(v.msgList))
    solo_run = 0

    conn.commit()
    conn.close()


def userAdapter(url):
    return [(ur.userID, ur.userName, ur.passwd, ur.privMask, ur.userInfo) for ur in url]

def groupAdapter(gpl):
    return [(gp.groupID, gp.creator, gp.groupName) for gp in gpl]

def groupMsgAdapter(msgl):
    return [(msg.targetID, msg.sendorID, int(msg.timestamp), msg.typeID, msg.msgText) for msg in msgl]
