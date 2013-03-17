# -*- coding: utf-8 -*- 
import sqlite3
import network
import logic
import db
if __name__=="__main__":
    conn = sqlite3.connect("ECR.db")
    c = conn.cursor()
    c.execute("delete from Message")
    conn.commit()
    conn.close()
    db.restoreFromDB("ECR.db",0);
    logic.addUser(7607, u"孤舟一叶", "123", u"我是孤舟一叶，我为自己带盐")
    db.saveToDB("ECR.db");