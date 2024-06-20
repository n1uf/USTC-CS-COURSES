import pymysql

# 存储过程
def db_procedures(db, cursor):

    # 1.修改课程ID
    try:
        cursor.execute("DROP PROCEDURE IF EXISTS updateClassID")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
    CREATE PROCEDURE updateClassID(IN old_id CHAR(12), IN new_id CHAR(12))
    BEGIN
        ALTER TABLE Scores
        DROP FOREIGN KEY Scores_cforeign;
        
        UPDATE Scores
        SET cid = new_id
        WHERE cid = old_id;

        UPDATE Courses
        SET cid = new_id
        WHERE cid = old_id;
        
        ALTER TABLE Scores
        ADD CONSTRAINT Scores_cforeign FOREIGN KEY (cid) REFERENCES Courses (cid);
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        cursor.execute("""
        ALTER TABLE Scores
        ADD CONSTRAINT Scores_cforeign FOREIGN KEY (cid) REFERENCES Courses (cid);
        """)
        return

    # 2.修改学号
    try:
        cursor.execute("DROP PROCEDURE IF EXISTS updateStudentID")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    try:
        cursor.execute("""
    CREATE PROCEDURE updateStudentID(IN old_id CHAR(12), IN new_id CHAR(12))
    BEGIN
        ALTER TABLE Scores
        DROP FOREIGN KEY Scores_sforeign;
        
        UPDATE Scores
        SET sid = new_id
        WHERE sid = old_id;
        
        ALTER TABLE Punish
        DROP FOREIGN KEY Punish_sforeign;
        
        UPDATE Punish
        SET sid = new_id
        WHERE sid = old_id;

        ALTER TABLE award
        DROP FOREIGN KEY award_sforeign;
        
        UPDATE award
        SET sid = new_id
        WHERE sid = old_id;

        UPDATE Students
        SET sid = new_id
        WHERE sid = old_id;
        
        ALTER TABLE Scores
        ADD CONSTRAINT Scores_sforeign FOREIGN KEY (sid) REFERENCES Students (sid);

        ALTER TABLE Punish
        ADD CONSTRAINT Punish_sforeign FOREIGN KEY (sid) REFERENCES Students (sid);

        ALTER TABLE Award
        ADD CONSTRAINT Award_sforeign FOREIGN KEY (sid) REFERENCES Students (sid);
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return