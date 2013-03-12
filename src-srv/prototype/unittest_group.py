import group
import user

uid = user.addUser("lzs","123456", "123456")
print "New user:", uid

gid = group.addGroup("NWSL", uid)

gp = group.findGroup(gid)
gp.postMsg(uid, "12345")
print gp.msgList[0]
