import sqlite3
if __name__=="__main__":
    conn = sqlite3.connect("ECR.db")
    c = conn.cursor()
    c.execute("delete from Message")
    conn.commit()
    conn.close()
