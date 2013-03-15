import network
import db
import session
import thread
import time

dbBackupIntv = 60
dbLoadRange = 3600*24
dbFilename = "ECR.db"

def dbGuard(dbname):
    db.restoreFromDB(dbname, int(time.time()-dbLoadRange))
    while(1):
        time.sleep(dbBackupIntv)
        network.requestMutex.acquire()
        print "Doing DB backup..."
        db.saveToDB(dbname)
        print "DB backup finished"
        network.requestMutex.release()

def bodyCleaner():
    while(1):
        time.sleep(session.KAI)
        network.requestMutex.acquire()
        print "Doing body cleaning..."
        session.cleanDeadUser()
        print "Body cleaning finished"
        network.requestMutex.release()
if __name__=="__main__":
    thread.start_new_thread(dbGuard, (dbFilename,))
    thread.start_new_thread(bodyCleaner,())
    network.main()