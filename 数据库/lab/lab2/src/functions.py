# 一些添加操作
# 1.添加学生
def add_student(db, cursor, sid, sname, sex, age, major, photo):
    try:
        cursor.execute("INSERT INTO Students (sid, sname, sex, age, major, photo) VALUES (%s, %s, %s, %s, %s, %s)", (sid, sname, sex, age, major, photo))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 2.添加课程
def add_course(db, cursor, cid, cname, credit):
    try:
        cursor.execute("INSERT INTO Courses (cid, cname, credit) VALUES (%s, %s, %s)", (cid, cname, credit))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 3.添加惩罚
def add_punishment(db, cursor, pname, plevel):
    try:
        cursor.execute("INSERT INTO Punishments (pname, plevel) VALUES (%s, %s)", (pname, plevel))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 4.添加奖励
def add_prize(db, cursor, aname, alevel):
    try:
        cursor.execute("INSERT INTO Prizes (aname, alevel) VALUES (%s, %s)", (aname, alevel))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 5.创建成绩
def add_score(db, cursor, sid, cid, score):
    try:
        cursor.execute("INSERT INTO Scores (sid, cid, score) VALUES (%s, %s, %s)", (sid, cid, score))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 6.添加奖励情况
def add_award(db, cursor, sid, aname, adate):
    try:
        cursor.execute("INSERT INTO Award (sid, aname, adate) VALUES (%s, %s, %s)", (sid, aname, adate))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 7.添加惩罚情况
def add_punish(db, cursor, sid, pname, pdate):
    try:
        cursor.execute("INSERT INTO Punish (sid, pname, pdate) VALUES (%s, %s, %s)", (sid, pname, pdate))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return


# 一些删除操作
# 1.删除学生
def del_student(db, cursor, sid):
    try:
        cursor.execute("DELETE FROM Students WHERE sid = %s", (sid,))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 2.删除课程
def del_course(db, cursor, cid):
    try:
        cursor.execute("DELETE FROM Courses WHERE cid = %s", (cid,))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 3.删除奖项
def del_prize(db, cursor, aname):
    try:
        cursor.execute("DELETE FROM Prizes WHERE aname = %s", (aname,))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 4.删除惩罚
def del_punishment(db, cursor, pname):
    try:
        cursor.execute("DELETE FROM Punishments WHERE pname = %s", (pname,))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 5.删除成绩
def del_score(db, cursor, sid, cid):
    try:
        cursor.execute("DELETE FROM Scores WHERE sid = %s AND cid = %s", (sid, cid))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 6.删除奖励情况
def del_award(db, cursor, sid, aname):
    try:
        cursor.execute("DELETE FROM Award WHERE sid = %s AND aname = %s", (sid, aname))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 7.删除惩罚情况
def del_punish(db, cursor, sid, pname):
    try:
        cursor.execute("DELETE FROM Punish WHERE sid = %s AND pname = %s", (sid, pname))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return


# 一些基本查询
# 1.查询整个学生列表
def get_students(db, cursor):
    try:
        cursor.execute("SELECT * FROM Students")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 2.查询整个课程列表
def get_courses(db, cursor):
    try:
        cursor.execute("SELECT * FROM Courses")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 3.查询整个奖项列表
def get_prizes(db, cursor):
    try:
        cursor.execute("SELECT * FROM Prizes")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 4.查询整个惩罚列表
def get_punishments(db, cursor):
    try:
        cursor.execute("SELECT * FROM Punishments")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 5.查询整个成绩列表
def get_scores(db, cursor):
    try:
        cursor.execute("SELECT * FROM Scores")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 6.查询整个奖励情况列表
def get_awards(db, cursor):
    try:
        cursor.execute("SELECT * FROM Award")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 7.查询整个惩罚情况列表
def get_punishs(db, cursor):
    try:
        cursor.execute("SELECT * FROM Punish")
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 特定条件下的查询(通过主键)
# 1.按照sid查询某个学生
def get_student(db, cursor, sid):
    try:
        cursor.execute("SELECT * FROM Students WHERE sid = %s", (sid,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 2.按照cid查询某个课程
def get_course(db, cursor, cid):
    try:
        cursor.execute("SELECT * FROM Courses WHERE cid = %s", (cid,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 3.查询某个学生的奖项
def get_student_awards(db, cursor, sid):
    try:
        cursor.execute("SELECT Award.aname, Prizes.alevel, Award.adate FROM Award, Prizes WHERE sid = %s AND Award.aname = Prizes.aname", (sid,))
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 4.查询某个学生的惩罚
def get_student_punishs(db, cursor, sid):
    try:
        cursor.execute("SELECT Punish.pname, Punishments.plevel, Punish.pdate FROM Punish, Punishments WHERE sid = %s AND Punish.pname = Punishments.pname", (sid,))
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 5.查询某个学生的成绩
def get_student_scores(db, cursor, sid):
    try:
        cursor.execute("""SELECT scores.cid, cname, score, credit 
                        FROM Scores, Courses, Students 
                        WHERE scores.cid = courses.cid
                        AND scores.sid = students.sid
                        AND scores.sid = %s""", (sid,))
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 6.查询某个学生某个课程的成绩
def get_student_score(db, cursor, sid, cid):
    try:
        cursor.execute("SELECT * FROM Scores WHERE sid = %s AND cid = %s", (sid, cid))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 7.查询某个学生某个奖项
def get_student_award(db, cursor, sid, aname):
    try:
        cursor.execute("SELECT Award.aname, Prizes.alevel, Award.adate FROM Award, Prizes WHERE sid = %s AND Award.aname = %s AND Award.aname = Prizes.aname", (sid, aname))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 8.查询某个学生某个惩罚
def get_student_punish(db, cursor, sid, pname):
    try:
        cursor.execute("SELECT Punish.pname, Punishments.plevel, Punish.pdate FROM Punish, Punishments WHERE sid = %s AND Punish.pname = %s AND Punish.pname = Punishments.pname", (sid, pname))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 9.查询某个奖项
def get_prize(db, cursor, aname):
    try:
        cursor.execute("SELECT * FROM Prizes WHERE aname = %s", (aname,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 10.查询某个惩罚
def get_punishment(db, cursor, pname):
    try:
        cursor.execute("SELECT * FROM Punishments WHERE pname = %s", (pname,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return



# 其他查询
# 1.按姓名查询学生
def get_student_by_name(db, cursor, sname):
    try:
        cursor.execute("SELECT * FROM Students WHERE sname = %s", (sname,))
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 2.按课程名查询课程
def get_course_by_name(db, cursor, cname):
    try:
        cursor.execute("SELECT * FROM Courses WHERE cname = %s", (cname,))
        result = cursor.fetchall()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 3.查询某个学生的总学分
def get_student_credit(db, cursor, sid):
    try:
        cursor.execute("SELECT GetTotalCredits(%s) as TotalCredits", (sid,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")
        return

# 4.查询某个学生的平均成绩
def get_student_average(db, cursor, sid):
    try:
        cursor.execute("SELECT GetAverageScore(%s) as AverageScore", (sid,))
        result = cursor.fetchone()
        return result
    except Exception as e:
        print(f"ERROR:{e}")

# 一些修改操作
# 1.修改课程属性
def change_course(db, cursor, ID, num, newinf):
    if (num == 1):
        func ="UPDATE courses SET cname = %s WHERE cid = %s"
    if (num == 2):
        func ="UPDATE courses SET credit = %s WHERE cid = %s"
    try:
        cursor.execute(func, (newinf, ID)) 
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 2.修改课程号
def change_courseid(db, cursor, old_id, new_id):
    try:
        cursor.execute("CALL updateClassID(%s, %s)", (old_id, new_id))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return

# 3.修改学生属性
def change_student(db, cursor, ID, num, newinf):
    if (num == 1):
        func = "UPDATE Students SET sname = %s WHERE sid = %s"
    if (num == 2):
        func = "UPDATE Students SET sex = %s WHERE sid = %s"
    if (num == 3):
        func = "UPDATE Students SET age = %s WHERE sid = %s"
    if (num == 4):
        func = "UPDATE Students SET major = %s WHERE sid = %s"
    if (num == 5):
        func = "UPDATE Students SET photo = %s WHERE sid = %s"
    try:
        cursor.execute(func, (newinf, ID)) 
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return 

# 4.修改学号
def change_studentid(db, cursor, old_id, new_id):
    try:
        cursor.execute("CALL updateStudentID(%s, %s)", (old_id, new_id))
        db.commit()
    except Exception as e:
        print(f"ERROR:{e}")
        db.rollback()
        return
