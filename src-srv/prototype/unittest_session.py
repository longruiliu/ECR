import unittest_group
import session
import time

print "Unit test for session is presenting \n With a sincere greeting^_^"
print unittest_group.uid

sid = session.registerSession(unittest_group.uid, "172.18.23.1")
print session.sessionList_uk
print session.sessionList_sk
print session.getUserIDBySession(sid)

for i in xrange(6):
    session.cleanDeadUser()
    session.renewUser(unittest_group.uid)
    print session.sessionList_uk
    print session.sessionList_sk
    print session.getUserIDBySession(sid)
    time.sleep(1)

