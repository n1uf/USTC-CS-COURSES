import pymysql

# 触发器
def db_triggers(db, cursor):

    # 删除操作删除关联内容
    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_delete_student")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    
    try:
        cursor.execute("""
    CREATE TRIGGER trg_delete_student
    BEFORE DELETE ON Students
    FOR EACH ROW
    BEGIN
        SELECT COUNT(*) INTO @count FROM Scores WHERE sid = OLD.sid;
        
        IF @count > 0 THEN
            DELETE FROM Scores WHERE sid = OLD.sid;
        END IF;
                
        SELECT COUNT(*) INTO @count FROM Punish WHERE sid = OLD.sid;
        
        IF @count > 0 THEN
            DELETE FROM Punish WHERE sid = OLD.sid;
        END IF;
                
        SELECT COUNT(*) INTO @count FROM award WHERE sid = OLD.sid;
        
        IF @count > 0 THEN
            DELETE FROM award WHERE sid = OLD.sid;
        END IF;
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_delete_class")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    
    try:
        cursor.execute("""
    CREATE TRIGGER trg_delete_class
    BEFORE DELETE ON Courses
    FOR EACH ROW
    BEGIN
        SELECT COUNT(*) INTO @count FROM Scores WHERE cid = OLD.cid;
        
        IF @count > 0 THEN
            DELETE FROM Scores WHERE cid = OLD.cid;
        END IF;
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_delete_punish")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
    CREATE TRIGGER trg_delete_punish
    BEFORE DELETE ON Punishments
    FOR EACH ROW
    BEGIN
        SELECT COUNT(*) INTO @count FROM Punish WHERE pname = OLD.pname;
        
        IF @count > 0 THEN
            DELETE FROM Punish WHERE pname = OLD.pname;
        END IF;  
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_delete_award")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
    CREATE TRIGGER trg_delete_award
    BEFORE DELETE ON Prizes
    FOR EACH ROW
    BEGIN               
        SELECT COUNT(*) INTO @count FROM award WHERE aname = OLD.aname;
        
        IF @count > 0 THEN
            DELETE FROM award WHERE aname = OLD.aname;
        END IF;
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    # 新增学生时，自动新增学生登录信息
    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_insert_student")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
    
    try:
        cursor.execute("""
    CREATE TRIGGER trg_insert_student
    AFTER INSERT ON Students
    FOR EACH ROW
    BEGIN
        INSERT INTO StuLogin (sid, password) VALUES (NEW.sid, '123456');
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    # 修改学生学号时，自动更新学生登录信息
    try:
        cursor.execute("DROP TRIGGER IF EXISTS trg_update_student")
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

    try:
        cursor.execute("""
    CREATE TRIGGER trg_update_student
    AFTER UPDATE ON Students
    FOR EACH ROW
    BEGIN
        UPDATE StuLogin SET sid = NEW.sid WHERE sid = OLD.sid;
    END
    """)
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return