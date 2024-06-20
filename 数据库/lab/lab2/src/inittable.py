import pymysql

def drop_table(db, cursor):
    
    try:
        cursor.execute("""
        DROP TABLE IF EXISTS StuLogin
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Punish
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Award
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Punishments
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Prizes
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Scores
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    
    try:
        cursor.execute( """
        DROP TABLE IF EXISTS Courses
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return


    try:
        cursor.execute("""
        DROP TABLE IF EXISTS Students 
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return


def create_table(db, cursor):
    
    try:
        cursor.execute("""
        CREATE TABLE Students (
        sid CHAR(12) PRIMARY KEY,
        sname VARCHAR(64) NOT NULL,
        sex VARCHAR(64) NOT NULL,
        age INT NOT NULL,
        major VARCHAR(64) NOT NULL,
        photo LONGBLOB
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Courses (
        cid CHAR(12) PRIMARY KEY,
        cname VARCHAR(64) NOT NULL,
        credit FLOAT NOT NULL
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Scores (
        sid CHAR(12) NOT NULL,
        cid CHAR(12) NOT NULL,
        score INT,
        PRIMARY KEY (sid, cid),
        CONSTRAINT Scores_sforeign FOREIGN KEY (sid) REFERENCES Students(sid),
        CONSTRAINT Scores_cforeign FOREIGN KEY (cid) REFERENCES Courses(cid)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Punishments (
        pname VARCHAR(64) NOT NULL,
        plevel VARCHAR(64),
        PRIMARY KEY (pname)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Punish (
        sid CHAR(12) NOT NULL,
        pname VARCHAR(64) NOT NULL,
        pdate DATE,
        CONSTRAINT Punish_sforeign FOREIGN KEY (sid) REFERENCES Students(sid),
        CONSTRAINT Punish_pforeign FOREIGN KEY (pname) REFERENCES Punishments(pname)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Prizes (
        aname VARCHAR(64) NOT NULL,
        alevel VARCHAR(64),
        PRIMARY KEY (aname)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE TABLE Award (
        sid CHAR(12) NOT NULL,
        aname VARCHAR(64) NOT NULL,
        adate DATE,
        CONSTRAINT Award_sforeign FOREIGN KEY (sid) REFERENCES Students(sid),
        CONSTRAINT Award_pforeign FOREIGN KEY (aname) REFERENCES Prizes(aname)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    
    try:
        cursor.execute("""
        CREATE TABLE StuLogin (
        sid CHAR(12),
        password VARCHAR(64) DEFAULT '123456' NOT NULL,
        PRIMARY KEY (sid),
        CONSTRAINT StuLogin_sforeign FOREIGN KEY (sid) REFERENCES Students(sid)
        )
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

def init_table(db, cursor):
    drop_table(db, cursor)
    create_table(db, cursor)