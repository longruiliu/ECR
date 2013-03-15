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
        thread.sleep(dbBackupIntv)
        network.requestMutex.acquire()
        db.saveToDB(dbname)
        network.requestMutex.release()

def bodyCleaner():
    while(1):
        thread.sleep(session.KAI)
        network.requestMutex.acquire()
        session.cleanDeadUser()
        network.requestMutex.release()
if __name__=="__main__":
    thread.start_new_thread(dbGuard, (dbFilename,))
    thread.start_new_thread(bodyCleaner,(None,))
    network.main()