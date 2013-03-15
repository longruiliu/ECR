import sqlite3
import user
import group

solo_run = 0

def restoreFromDB(dbFileName, timeL):
    """
    Read data from database illustrated by dbFileName
    timeL specify the how old message you want get out of database
    every message from now - timeL to now while be restore
    """
    pass
    conn = sqlite3.connnect(dbFileName)
    c = conn.cursor()
    results = c.execute("select * from User")
    for result in results:
	tmp = user.User()
	tmp.userID = result["user_id"]
	tmp.userName = result["u_name"]
	tmp.passwd = result["pwd"]
	tmp.userInfo = result["info"]
	tmp.privMask = result["previlege"]
	user.userList[tmp.userId] = tmp

    results = c.execute("select * from Group_list")
    for result in results:
        tmp = group.Group()
	tmp.groupID = result["group_id"]
	tmp.creator = result["creator_id"]
	tmp.groupName = result["g_name"]
	group.groupList[tmp.groupID] = tmp

    results = c.execute("select user_id,group_id from User_Group")
    for result in results:
        g = findGroup(result["group_id"])
	u = findUser(result["user_id"])
	g.groupMember[u.userID] = u

    results = c.execute("select & from Message where send_time > ?",timeL)
    for result in results:
        g = findGroup(result["group_id"])
	tmp = msgRecord.MsgRecord()
	tmp.sendorID = result["user_id"]
	tmp.targetID = result["group_id"]
	tmp.msgText = result["content"]
	tmp.timestamp = result["send_time"]
	tmp.typeID = result["m_type"]
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
    c.executemany("insert into User(user_id, u_name, pwd, previlege, info) values(?)", (user.userList.values(),))

    c.execute("delete  from Group")
    c.executemany("insert into Group_list(group_id, creator_id, g_name) values(?)", (group.groupList.values(),))

    c.execute("delete  from User_Group")
    for v in group.groupList.values():
        c.executemany("insert into User_Group(user_id, group_id) values(?, ?)", [(r, v.groupID) for r in v.groupMember.keys()])

    c.execute("delete * from Message")
    for gp in group.groupList.values():
    	c.executemany("insert into Message(group_id, user_id, send_time, m_type, content) values(?)", v.msgList)
    solo_run = 0

    conn.commit()
    conn.close()


def userAdapter(ur):
    return "%d, %s, %s, %d, %s" % (ur.userID, ur.UserName, ur.passwd, ur.userInfo, ur.privMask)

def groupAdapter(gp):
    return "%d %d %s" % (gp.groupID, gp.creator, gp.groupName)

def groupMsgAdapter(msg):
    return "%d, %d, %d, %d, %s" % (msg.targetID, msg.sendorID, int(msg.timestamp), msg.typeID, msg.msgText)
