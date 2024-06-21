import pymysql

# 创建函数
def db_functions(db, cursor):
    
    # 查询某个学生的总学分
    try:
        cursor.execute("DROP Function IF EXISTS GetTotalCredits")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE FUNCTION GetTotalCredits (stuid CHAR(12)) RETURNS FLOAT
    DETERMINISTIC
    BEGIN
        DECLARE total_Credits FLOAT;
        SELECT SUM(Courses.credit) INTO total_Credits
        FROM Courses
        WHERE cid IN (SELECT cid FROM Scores WHERE Scores.sid = stuid);
        RETURN total_Credits;
    END
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    # 查询某个学生的平均成绩
    try:
        cursor.execute("DROP Function IF EXISTS GetAverageScore")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
        CREATE FUNCTION GetAverageScore (stuid CHAR(12)) RETURNS FLOAT
    DETERMINISTIC
    BEGIN
        DECLARE total_Score FLOAT;
        DECLARE total_Credits FLOAT;
        SELECT SUM(Scores.score * Courses.credit) INTO total_Score
        FROM Scores, Courses
        WHERE Scores.cid = Courses.cid AND Scores.sid = stuid;
        SELECT SUM(Courses.credit) INTO total_Credits
        FROM Courses
        WHERE cid IN (SELECT cid FROM Scores WHERE Scores.sid = stuid);
        RETURN total_Score / total_Credits;
    END
        """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return