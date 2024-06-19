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
        CREATE FUNCTION GetTotalCredits (stuid CHAR(12)) RETURNS INT
    DETERMINISTIC
    BEGIN
        DECLARE total_Credits INT;
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