import user
uid = user.addUser("root", "123456", "lcl")
ur = user.findUser(uid)
ur.privMask = 0x7

print "New root user:%d" %(uid,)

