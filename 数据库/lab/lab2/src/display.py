import sys
import io
from PyQt6.QtWidgets import QApplication, QWidget, QPushButton, QVBoxLayout, QGroupBox, QHBoxLayout, QMessageBox
from PyQt6.QtWidgets import QTabWidget, QGridLayout, QLineEdit, QLabel, QFileDialog, QDialog, QTableWidget, QTableWidgetItem
from PyQt6.QtCore import QByteArray
from PyQt6.QtGui import QIcon, QPixmap, QImage, QColor 

from PIL import Image

import inittable
import db_functions
import db_procedures
import db_triggers
import functions



class AddStudentWindow(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.ID = ''
        self.name = ''
        self.sex = ''
        self.age = 0
        self.major = ''
        self.photo = ''
        self.setWindowTitle('输入新学生信息')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("学号：")
        self.label2 = QLabel("姓名：")
        self.label3 = QLabel("性别：")
        self.label4 = QLabel("年龄：")
        self.label5 = QLabel("专业：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的学号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入姓名...")
        self.input_box3 = QLineEdit(self)
        self.input_box3.setPlaceholderText("在此输入性别(M/F)...")
        self.input_box4 = QLineEdit(self)
        self.input_box4.setPlaceholderText("在此输入年龄...")
        self.input_box5 = QLineEdit(self)
        self.input_box5.setPlaceholderText("在此输入专业...")

        # 创建上传照片按钮
        self.chooseButton = QPushButton('选择要上传的照片', self)
        self.chooseButton.clicked.connect(self.choosePhoto)

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label3)
        layout3.addWidget(self.input_box3)
        layout4 = QHBoxLayout()
        layout4.addWidget(self.label4)
        layout4.addWidget(self.input_box4)
        layout5 = QHBoxLayout()
        layout5.addWidget(self.label5)
        layout5.addWidget(self.input_box5)
        layout6 = QHBoxLayout()
        layout6.addWidget(self.chooseButton)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(layout3)
        layout.addLayout(layout4)
        layout.addLayout(layout5)
        layout.addLayout(layout6)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        self.acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            self.acceptflag += 1
            self.ID = self.input_box1.text()
            info = functions.get_student(self.db, self.cursor, self.ID)
            if (info != None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '该学号已存在') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box2.text()) != 0):
            self.acceptflag += 1
            self.name = self.input_box2.text()
        
        if (len(self.input_box3.text()) != 0):
            try:
                self.sex = self.input_box3.text()
                assert(self.sex == 'M' or self.sex == 'F')
                self.acceptflag += 1
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '性别输入有误') #触发的事件时弹出会话框
                return

        if (len(self.input_box4.text()) != 0):
            try:
                self.age = int(self.input_box4.text())
                assert(self.age > 10 and self.age < 40)
                self.acceptflag += 1
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '年龄不合法') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box5.text()) != 0):
            self.acceptflag += 1
            self.major = self.input_box5.text()

        if self.acceptflag == 5:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框


    def choosePhoto(self):
        photo_path, _ = QFileDialog.getOpenFileName(self, "Select Photo", "", "Image Files (*.png *.jpg *.jpeg *.bmp)")
        if photo_path:
            # 打开图片并调整尺寸
            fixed_size = (50, 50)  # 固定尺寸 (宽度, 高度)
            with Image.open(photo_path) as img:
                if img.mode == 'RGBA':
                    img = img.convert('RGB')
                img = img.resize(fixed_size, Image.LANCZOS)
                # 将调整尺寸后的图片保存为字节数据
                temp_image_path = "temp_image.jpg"
                img.save(temp_image_path, format="JPEG")
                with open(temp_image_path, "rb") as picture:
                    self.photo = picture.read()

    def get_entered_ID(self):
        return self.ID
    
    def get_entered_Name(self):
        return self.name

    def get_entered_Sex(self):
        return self.sex
    
    def get_entered_Age(self):
        return self.age
    
    def get_entered_Major(self):
        return self.major
        
    def get_entered_Photo(self):
        return self.photo

class AddClassWindow(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.ID = ''
        self.name = ''
        self.credit = 0
        self.setWindowTitle('输入新课程信息')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("课程号：")
        self.label2 = QLabel("课程名：")
        self.label3 = QLabel("学分：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的课程号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入课程名...")
        self.input_box3 = QLineEdit(self)
        self.input_box3.setPlaceholderText("在此输入学分...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label3)
        layout3.addWidget(self.input_box3)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(layout3)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.ID = self.input_box1.text()
            info = functions.get_course(self.db, self.cursor, self.ID)
            if (info != None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '该课程号已存在') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.name = self.input_box2.text()
        
        if (len(self.input_box3.text()) != 0):
            try:
                self.credit = float(self.input_box3.text())
                assert(self.credit > 0 and self.credit < 5)
                acceptflag += 1
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学分不合法') #触发的事件时弹出会话框
                return

        if acceptflag == 3:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框


    def get_entered_ID(self):
        return self.ID
    
    def get_entered_Name(self):
        return self.name
    
    def get_entered_Credit(self):
        return self.credit

class AddPrizeWindow(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.grade = ''
        self.name = ''
        self.setWindowTitle('输入新奖项信息')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("奖项：")
        self.label2 = QLabel("等级：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的奖项...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入等级...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.name = self.input_box1.text()
            info = functions.get_prize(self.db, self.cursor, self.name)
            if (info != None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '该奖项已存在') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.grade = self.input_box2.text()

        if acceptflag == 2:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框

    def get_entered_Name(self):
        return self.name
    
    def get_entered_Grade(self):
        return self.grade
    
class AddPunishmentWindow(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.name = ''
        self.grade = ''
        self.setWindowTitle('输入新惩罚信息')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("惩罚：")
        self.label2 = QLabel("等级：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的惩罚...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入等级...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.name = self.input_box1.text()
            info = functions.get_punishment(self.db, self.cursor, self.name)
            if (info != None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '该惩罚已存在') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.grade = self.input_box2.text()

        if acceptflag == 2:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框

    def get_entered_Name(self):
        return self.name
    
    def get_entered_Grade(self):
        return self.grade

class AddPASWindow(QDialog):
    def __init__(self, db, cursor, kind):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.kind = kind
        self.ID = ''
        self.name = ''
        self.timescore = ''
        if self.kind == 0:
            self.setWindowTitle('输入获奖学生的学号和奖项信息')
        if kind == 1:
            self.setWindowTitle('输入受惩学生的学号和惩罚信息')
        if kind == 2:
            self.setWindowTitle('输入学生的学号和课程号')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("学生学号：")
        if self.kind == 0:
            self.label2 = QLabel("奖项名称：")
            self.label3 = QLabel("时间：")
        if self.kind == 1:
            self.label2 = QLabel("惩罚名称：")
            self.label3 = QLabel("时间：")
        if self.kind == 2:
            self.label2 = QLabel("课程号：")
            self.label3 = QLabel("成绩：")
        
        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入学号...")
        self.input_box2 = QLineEdit(self)
        if self.kind == 2:
            self.input_box2.setPlaceholderText("在此输入课程号...")
        else:
            self.input_box2.setPlaceholderText("在此输入名称...")
        self.input_box3 = QLineEdit(self)
        if self.kind == 2:
            self.input_box3.setPlaceholderText("在此输入成绩...")
        else:
            self.input_box3.setPlaceholderText("在此输入时间...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label3)
        layout3.addWidget(self.input_box3)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(layout3)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.ID = self.input_box1.text()
            info = functions.get_student(self.db, self.cursor, self.ID)
            if (info == None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学生不存在') #触发的事件时弹出会话框
                return
            
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.name = self.input_box2.text()

        if acceptflag == 2:
            if self.kind == 0:
                info = functions.get_prize(self.db, self.cursor, self.name)
                if (info == None):
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '奖项不存在') #触发的事件时弹出会话框
                    return
                info = functions.get_student_award(self.db, self.cursor, self.ID, self.name)
            if self.kind == 1:
                info = functions.get_punishment(self.db, self.cursor, self.name)
                if (info == None):
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '惩罚不存在') #触发的事件时弹出会话框
                    return
                info = functions.get_student_punish(self.db, self.cursor, self.ID, self.name)
            if self.kind == 2:
                info = functions.get_course(self.db, self.cursor, self.name)
                if (info == None):
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '课程不存在') #触发的事件时弹出会话框
                    return
                info = functions.get_student_score(self.db, self.cursor, self.ID, self.name)
            if (info != None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '已存在') #触发的事件时弹出会话框
                return

        if (len(self.input_box3.text()) != 0):
            acceptflag += 1
            self.timescore = self.input_box3.text()

        if acceptflag == 3:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框    

    def get_entered_ID(self):
        return self.ID
    
    def get_entered_Name(self):
        return self.name
    
    def get_entered_timescore(self):
        return self.timescore

class ShowAllTable(QWidget):
    def __init__(self, db, cursor, kind, name = ''):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.kind = kind
        self.name = name
        tablename = ['学生名单','课程','学生名单','奖项','惩罚']
        self.setWindowTitle(tablename[kind])
        self.resize(600, 750)
        self.init_ui()
    
    def init_ui(self):
        if (self.kind == 0):
            info = functions.get_students(self.db, self.cursor)
        if (self.kind == 1):
            info = functions.get_courses(self.db, self.cursor)
        if (self.kind == 2):
            info = functions.get_student_by_name(self.db, self.cursor, self.name)
        if (self.kind == 3):
            info = functions.get_prizes(self.db, self.cursor)
        if (self.kind == 4):
            info = functions.get_punishments(self.db, self.cursor)
        #print(info)
        # 创建表格
        try:
            if (self.kind == 0 or self.kind == 2):
                leninfo = 5
                self.table = QTableWidget(len(info), leninfo)
                self.table.setHorizontalHeaderLabels(['学号','姓名','性别','年龄','专业'])
            if (self.kind == 1):
                leninfo = 3
                self.table = QTableWidget(len(info), leninfo)
                self.table.setHorizontalHeaderLabels(['课程号','课程名','学分'])
            if (self.kind == 3):
                leninfo = 2
                self.table = QTableWidget(len(info), leninfo)
                self.table.setHorizontalHeaderLabels(['奖项','等级'])
            if (self.kind == 4):
                leninfo = 2
                self.table = QTableWidget(len(info), leninfo)
                self.table.setHorizontalHeaderLabels(['惩罚','等级'])

        except Exception as e:
            print(f"ERROR:{e}")
            return
        
        # 填充表格数据
        for i in range(len(info)):
            for j in range(leninfo):
                    item = QTableWidgetItem(str(info[i][j]))
                    self.table.setItem(i, j, item)

        # 创建关闭按钮
        self.closeButton = QPushButton('Close', self)
        self.closeButton.clicked.connect(self.close)

        # 设置布局
        layout = QVBoxLayout()
        layout.addWidget(self.table)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

class GetStudentinfoById(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.sid, self.sname, self.sex, self.age, self.major, self.photo = '', '', '', 1, '', ''
        self.setWindowTitle('输入需要查询的学生学号')
        self.resize(320, 200)
        self.init_ui()

    def init_ui(self):

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入学号...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.input_box1)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        self.acceptflag = False
        if (len(self.input_box1.text()) != 0):
            self.sid = self.input_box1.text()
            info = functions.get_student(self.db, self.cursor, self.sid)
            if info == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学生不存在') #触发的事件时弹出会话框
            else:
                self.acceptflag = True
                self.sname = info[1]
                self.sex = info[2]
                self.age = info[3]
                self.major = info[4]
                self.photo = info[5]

        if self.acceptflag:
            self.accept()

    def get_entered_ID(self):
        return self.sid
    
    def get_entered_Name(self):
        return self.sname

    def get_entered_sex(self):
        return self.sex
    
    def get_entered_Age(self):
        return self.age
    
    def get_entered_Major(self):
        return self.major
        
    def get_entered_Photo(self):
        return self.photo

class Studentinfo(QWidget):
    def __init__(self, db, cursor, sid, sname, sex, age, major, photo):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.sid = sid
        self.sname = sname
        self.sex = sex
        self.age = age
        self.major = major
        self.photo = photo
        self.setWindowTitle('学生详细信息')
        self.resize(600, 750)
        self.init_ui()
    
    def init_ui(self):
        scoreinfo = functions.get_student_scores(self.db, self.cursor, self.sid)
        punishinfo = functions.get_student_punishs(self.db, self.cursor, self.sid)
        prizeinfo = functions.get_student_awards(self.db, self.cursor, self.sid)
        if (len(scoreinfo)!=0):
            credits_info = functions.get_student_credit(self.db, self.cursor, self.sid)
            credit = credits_info[0]
            ave_score_info = functions.get_student_average(self.db, self.cursor, self.sid)
            ave_score = ave_score_info[0]
        else:
            credit = 0
            ave_score = 0

        # 创建 QLabel 对象
        self.label1 = QLabel(f"学号：{self.sid}")
        self.label2 = QLabel(f"姓名：{self.sname}")
        self.label3 = QLabel(f"性别：{self.sex}")
        self.label4 = QLabel(f"年龄：{self.age}")
        self.label5 = QLabel(f"专业：{self.major}")
        self.label6 = QLabel(f"当前已获总学分：{credit}")   
        self.label7 = QLabel(f"当前平均成绩：{ave_score}")
        try:
            image = QImage.fromData(QByteArray(self.photo))
            pixmap = QPixmap(image)
            self.label8 = QLabel(self)
            self.label8.setPixmap(pixmap)
        except Exception as e:
            print(f"ERROR:{e}")
            return

        # 创建表格
        self.table1 = QTableWidget(len(scoreinfo), 4)
        self.table1.setHorizontalHeaderLabels(['课程号','课程名','成绩','学分'])
        # 填充表格数据
        for i in range(len(scoreinfo)):
            for j in range(4):
                    item = QTableWidgetItem(str(scoreinfo[i][j]))
                    self.table1.setItem(i, j, item)
        # 创建表格
        self.table2 = QTableWidget(len(punishinfo), 3)
        self.table2.setHorizontalHeaderLabels(['惩罚项目','惩罚等级','时间'])
        # 填充表格数据
        for i in range(len(punishinfo)):
            for j in range(3):
                    item = QTableWidgetItem(str(punishinfo[i][j]))
                    self.table2.setItem(i, j, item)

        # 创建表格
        self.table3 = QTableWidget(len(prizeinfo), 3)
        self.table3.setHorizontalHeaderLabels(['奖项','奖励等级','时间'])
        # 填充表格数据
        for i in range(len(prizeinfo)):
            for j in range(3):
                    item = QTableWidgetItem(str(prizeinfo[i][j]))
                    self.table3.setItem(i, j, item)

        # 创建关闭按钮
        self.closeButton = QPushButton('Close', self)
        self.closeButton.clicked.connect(self.close)

        # 设置布局
        layout = QVBoxLayout()
        layout_base = QHBoxLayout()
        layout_base1 = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.label2)
        layout1.addWidget(self.label3)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label4)
        layout2.addWidget(self.label5)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label6)
        layout3.addWidget(self.label7)
        layout_base1.addLayout(layout1)
        layout_base1.addLayout(layout2)
        layout_base1.addLayout(layout3)
        layout_base.addLayout(layout_base1)
        layout_base.addWidget(self.label8)
        layout.addLayout(layout_base)
        layout.addWidget(self.table1)
        layout.addWidget(self.table2)
        layout.addWidget(self.table3)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

class ChangeStudentWindow(QDialog):
    def __init__(self, db, cursor, oldinfo):
        super().__init__()
        self.db = db
        self.ID = oldinfo[0]
        self.name = oldinfo[1]
        self.sex = oldinfo[2]
        self.age = oldinfo[3]
        self.major = oldinfo[4]
        self.photo = oldinfo[5]
        self.acceptflag = False
        self.setWindowTitle(f'请输入要修改的内容，不需要修改则留空')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel(f"从{self.ID}修改为：")
        self.label2 = QLabel(f"从{self.name}修改为：")
        self.label3 = QLabel(f"从{self.sex}修改为：")
        self.label4 = QLabel(f"从{self.age}修改为：")
        self.label5 = QLabel(f"从{self.major}修改为：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的学号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入新的姓名...")
        self.input_box3 = QLineEdit(self)
        self.input_box3.setPlaceholderText("在此输入新的性别(M/F)...")
        self.input_box4 = QLineEdit(self)
        self.input_box4.setPlaceholderText("在此输入新的年龄...")
        self.input_box5 = QLineEdit(self)
        self.input_box5.setPlaceholderText("在此输入新的专业...")

        # 创建上传照片按钮
        self.chooseButton = QPushButton('选择要上传的照片', self)
        self.chooseButton.clicked.connect(self.choosePhoto)

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label3)
        layout3.addWidget(self.input_box3)
        layout4 = QHBoxLayout()
        layout4.addWidget(self.label4)
        layout4.addWidget(self.input_box4)
        layout5 = QHBoxLayout()
        layout5.addWidget(self.label5)
        layout5.addWidget(self.input_box5)
        layout6 = QHBoxLayout()
        layout6.addWidget(self.chooseButton)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(layout3)
        layout.addLayout(layout4)
        layout.addLayout(layout5)
        layout.addLayout(layout6)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        
        if (len(self.input_box1.text()) != 0):
            self.acceptflag = True
            self.ID = self.input_box1.text()
        if (len(self.input_box2.text()) != 0):
            self.acceptflag = True
            self.name = self.input_box2.text()
        
        if (len(self.input_box3.text()) != 0):
            try:
                self.sex = self.input_box3.text()
                assert(self.sex == 'M' or self.sex == 'F')
                self.acceptflag = True
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '性别输入有误') #触发的事件时弹出会话框

        if (len(self.input_box4.text()) != 0):
            try:
                self.age = int(self.input_box4.text())
                assert(self.age > 10 and self.age < 40)
                self.acceptflag = True
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '年龄不合法') #触发的事件时弹出会话框
        
        if (len(self.input_box5.text()) != 0):
            self.acceptflag = True
            self.major = self.input_box5.text()

        if self.acceptflag:
            self.accept()

    def choosePhoto(self):
        photo_path, _ = QFileDialog.getOpenFileName(self, "Select Photo", "", "Image Files (*.png *.jpg *.jpeg *.bmp)")
        if photo_path:
            # 打开图片并调整尺寸
            fixed_size = (50, 50)  # 固定尺寸 (宽度, 高度)
            with Image.open(photo_path) as img:
                if img.mode == 'RGBA':
                    img = img.convert('RGB')
                img = img.resize(fixed_size, Image.LANCZOS)
                # 将调整尺寸后的图片保存为字节数据
                temp_image_path = "temp_image.jpg"
                img.save(temp_image_path, format="JPEG")
                with open(temp_image_path, "rb") as picture:
                    self.photo = picture.read()
                    self.acceptflag = True

    def get_entered_ID(self):
        return self.ID
    
    def get_entered_Name(self):
        return self.name

    def get_entered_Sex(self):
        return self.sex
    
    def get_entered_Age(self):
        return self.age
    
    def get_entered_Major(self):
        return self.major
        
    def get_entered_Photo(self):
        return self.photo

class ChangeClassWindow(QDialog):
    def __init__(self, db, cursor, oldinfo):
        super().__init__()
        self.ID = oldinfo[0]
        self.name = oldinfo[1]
        self.credit = oldinfo[2]
        self.setWindowTitle(f'请输入要修改的内容，不需要修改则留空')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel(f"从{self.ID}修改为：")
        self.label2 = QLabel(f"从{self.name}修改为：")
        self.label3 = QLabel(f"从{self.credit}修改为：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入新的课程号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入新的课程名...")
        self.input_box3 = QLineEdit(self)
        self.input_box3.setPlaceholderText("在此输入新的学分...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        layout3 = QHBoxLayout()
        layout3.addWidget(self.label3)
        layout3.addWidget(self.input_box3)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(layout3)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = False
        if (len(self.input_box1.text()) != 0):
            acceptflag = True
            self.ID = self.input_box1.text()
        if (len(self.input_box2.text()) != 0):
            acceptflag = True
            self.name = self.input_box2.text()
        if (len(self.input_box3.text()) != 0):
            try:
                self.credit = int(self.input_box3.text())
                assert(self.credit > 0 and self.credit < 5)
                acceptflag = True
            except Exception as e:
                print(f"ERROR:{e}")
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学分不合法') #触发的事件时弹出会话框
        if acceptflag:
            self.accept()

    def get_entered_ID(self):
        return self.ID
    
    def get_entered_Name(self):
        return self.name
    
    def get_entered_Credit(self):
        return self.credit

class DeleteScoreWindow(QDialog):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.sid = ''
        self.cid = ''
        self.setWindowTitle('输入要删除的学生学号和课程号')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("学生学号：")
        self.label2 = QLabel("课程号：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入学号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入课程号...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.sid = self.input_box1.text()
            
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.cid = self.input_box2.text()

        if acceptflag == 2:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息') #触发的事件时弹出会话框    

    def get_entered_sid(self):
        return self.sid
    
    def get_entered_cid(self):
        return self.cid

class DeletePAWindow(QDialog):
    def __init__(self, db, cursor, kind):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.kind = kind
        self.setWindowTitle('输入要删除的学号和奖项/惩罚')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLabel 对象
        self.label1 = QLabel("学号：")
        self.label2 = QLabel("奖项/惩罚：")

        # 创建 QLineEdit 对象
        self.input_box1 = QLineEdit(self)
        self.input_box1.setPlaceholderText("在此输入学号...")
        self.input_box2 = QLineEdit(self)
        self.input_box2.setPlaceholderText("在此输入奖项/惩罚...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout1 = QHBoxLayout()
        layout1.addWidget(self.label1)
        layout1.addWidget(self.input_box1)
        layout2 = QHBoxLayout()
        layout2.addWidget(self.label2)
        layout2.addWidget(self.input_box2)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(layout1)
        layout.addLayout(layout2)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        acceptflag = 0
        if (len(self.input_box1.text()) != 0):
            acceptflag += 1
            self.ID = self.input_box1.text()
            info = functions.get_student(self.db, self.cursor, self.ID)
            if (info == None):
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学生不存在') #触发的事件时弹出会话框
                return
        if (len(self.input_box2.text()) != 0):
            acceptflag += 1
            self.ID = self.input_box1.text()
            self.name = self.input_box2.text()
            if self.kind == 0:
                info = functions.get_student_award(self.db, self.cursor, self.ID, self.name)
                if (info == None):
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '该学生没有该奖项') #触发的事件时弹出会话框
                    return
            if self.kind == 1:
                info = functions.get_student_punish(self.db, self.cursor, self.ID, self.name)
                if (info == None):
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '该学生没有该惩罚')
                    return

        if acceptflag == 2:
            self.accept()
        else:
            widget = QWidget()
            QMessageBox.information(widget, '信息', '缺少信息')

    def get_entered_ID(self):
        return self.input_box1.text()
    
    def get_entered_Name(self):
        return self.input_box2.text()

class EnterSingleText(QDialog):
    def __init__(self, action, content):
        super().__init__()
        self.text = ''
        self.setWindowTitle(f'请输入要{action}的{content}')
        self.resize(320, 200)
        self.init_ui()
    
    def init_ui(self):
        # 创建 QLineEdit 对象
        self.input_box = QLineEdit(self)
        self.input_box.setPlaceholderText("在此输入...")

        # 创建确认按钮
        self.closeButton = QPushButton('确认', self)
        self.closeButton.clicked.connect(self.get_text)

        # 设置布局
        layout = QVBoxLayout()
        layout.addWidget(self.input_box)
        bottomLayout = QHBoxLayout()
        bottomLayout.addWidget(self.closeButton)
        layout.addLayout(bottomLayout)
        self.setLayout(layout)

    def get_text(self):
        self.text = self.input_box.text()
        self.accept()

    def get_entered_text(self):
        return self.text

class Main_Window(QWidget):
    def __init__(self, db, cursor):
        super().__init__()
        self.db = db
        self.cursor = cursor
        self.setWindowTitle('学籍管理系统')
        self.resize(800, 600)
        
        self.init_ui()
        
    def init_ui(self):
        main_layout = QVBoxLayout()

        # 创建选项卡
        tab_widget = QTabWidget()
        tab_widget.addTab(self.create_add_box(), '添加操作')
        tab_widget.addTab(self.create_query_box(), '查询操作')
        tab_widget.addTab(self.create_modify_box(), '修改操作')
        tab_widget.addTab(self.create_delete_box(), '删除操作')
        tab_widget.addTab(self.create_reset_button(), '重置操作')

        # 将选项卡添加到主布局
        main_layout.addWidget(tab_widget)
        self.setLayout(main_layout)

    def create_add_box(self):
        box = QGroupBox('添加操作')
        layout = QGridLayout()

        buttons = [
            ('新增学生', self.add_student),
            ('新增课程', self.add_class),
            ('新增奖项', self.add_prize),
            ('新增惩罚', self.add_punishment),
            ('为学生添加惩罚', self.add_punish_for_student),
            ('为学生添加奖项', self.add_prize_for_student),
            ('新增成绩', self.add_score)
        ]

        for i, (text, slot) in enumerate(buttons):
            btn = QPushButton(text)
            btn.setMinimumSize(100, 50)  # 设置按钮最小尺寸
            btn.clicked.connect(slot)
            layout.addWidget(btn, i // 2, i % 2)  # 2列布局

        box.setLayout(layout)
        return box

    def create_query_box(self):
        box = QGroupBox('查询操作')
        layout = QGridLayout()

        buttons = [
            ('查看学生名单', self.check_all_students),
            ('查看全部课程', self.check_all_classes),
            ('按姓名查询', self.check_student_name),
            ('学号查询具体信息', self.check_student_info),
            ('查看全部奖项', self.check_all_prizes),
            ('查看全部惩罚', self.check_all_punishments)
        ]

        for i, (text, slot) in enumerate(buttons):
            btn = QPushButton(text)
            btn.setMinimumSize(100, 50)  # 设置按钮最小尺寸
            btn.clicked.connect(slot)
            layout.addWidget(btn, i // 2, i % 2)  # 2列布局

        box.setLayout(layout)
        return box

    def create_modify_box(self):
        box = QGroupBox('修改操作')
        layout = QGridLayout()

        buttons = [
            ('修改课程信息', self.change_class),
            ('修改学生信息', self.change_student)
        ]

        for i, (text, slot) in enumerate(buttons):
            btn = QPushButton(text)
            btn.setMinimumSize(100, 50)  # 设置按钮最小尺寸
            btn.clicked.connect(slot)
            layout.addWidget(btn, i // 2, i % 2)  # 2列布局

        box.setLayout(layout)
        return box

    def create_delete_box(self):
        box = QGroupBox('删除操作')
        layout = QGridLayout()

        buttons = [
            ('删除学生', self.delete_student),
            ('删除课程', self.delete_class),
            ('删除奖项', self.delete_prize),
            ('删除惩罚', self.delete_punishment),
            ('删除成绩', self.delete_score),
            ('删除学生奖项', self.delete_prize_for_student),
            ('删除学生惩罚', self.delete_punish_for_student)
        ]

        for i, (text, slot) in enumerate(buttons):
            btn = QPushButton(text)
            btn.setMinimumSize(100, 50)  # 设置按钮最小尺寸
            btn.clicked.connect(slot)
            layout.addWidget(btn, i // 2, i % 2)  # 2列布局

        box.setLayout(layout)
        return box

    def create_reset_button(self):
        box = QGroupBox('重置操作')
        layout = QGridLayout()

        buttons = [
            ('重置数据库', self.confirm_reset_db),
            ('重置函数等', self.confirm_update_func)
        ]

        for i, (text, slot) in enumerate(buttons):
            btn = QPushButton(text)
            btn.setMinimumSize(100, 50)  # 设置按钮最小尺寸
            btn.clicked.connect(slot)
            layout.addWidget(btn, i // 2, i % 2)  # 2列布局

        box.setLayout(layout)
        return box


    def add_student(self):
        self.newWindow = AddStudentWindow(self.db, self.cursor)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newSex = self.newWindow.get_entered_Sex()
            newAge = self.newWindow.get_entered_Age()
            newMajor = self.newWindow.get_entered_Major()
            newPhoto = self.newWindow.get_entered_Photo()
            functions.add_student(self.db, self.cursor, newID, newName, newSex, newAge, newMajor, newPhoto)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框
    
    def add_class(self):
        self.newWindow = AddClassWindow(self.db, self.cursor)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newCredit = self.newWindow.get_entered_Credit()
            functions.add_course(self.db, self.cursor, newID, newName, newCredit)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    def add_prize(self):
        self.newWindow = AddPrizeWindow(self.db, self.cursor)
        if self.newWindow.exec():
            newName = self.newWindow.get_entered_Name()
            newGrade = self.newWindow.get_entered_Grade()
            functions.add_prize(self.db, self.cursor, newName, newGrade)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    def add_punishment(self):
        self.newWindow = AddPunishmentWindow(self.db, self.cursor)
        if self.newWindow.exec():
            newName = self.newWindow.get_entered_Name()
            newGrade = self.newWindow.get_entered_Grade()
            functions.add_punishment(self.db, self.cursor, newName, newGrade)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    def add_prize_for_student(self):
        self.newWindow = AddPASWindow(self.db, self.cursor, 0)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newTime = self.newWindow.get_entered_timescore()
            functions.add_award(self.db, self.cursor, newID, newName, newTime)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    def add_punish_for_student(self):
        self.newWindow = AddPASWindow(self.db, self.cursor, 1)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newTime = self.newWindow.get_entered_timescore()
            functions.add_punish(self.db, self.cursor, newID, newName, newTime)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    def add_score(self):
        self.newWindow = AddPASWindow(self.db, self.cursor, 2)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newScore = self.newWindow.get_entered_timescore()
            functions.add_score(self.db, self.cursor, newID, newName, newScore)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '添加成功') #触发的事件时弹出会话框

    

    def check_all_students(self):
        self.tableWindow = ShowAllTable(self.db, self.cursor, 0, '')
        self.tableWindow.show()
    
    def check_all_classes(self):
        self.tableWindow = ShowAllTable(self.db, self.cursor, 1, '')
        self.tableWindow.show()

    def check_student_name(self):
        getname = EnterSingleText('查询','姓名')
        if getname.exec():
            # 如果用户点击确认按钮，则获取输入的文本
            name = getname.get_entered_text()
            self.tableWindow = ShowAllTable(self.db, self.cursor, 2, name)
            self.tableWindow.show()
    
    def check_student_info(self):
        self.newWindow = GetStudentinfoById(self.db, self.cursor)
        if self.newWindow.exec():
            newID = self.newWindow.get_entered_ID()
            newName = self.newWindow.get_entered_Name()
            newSex = self.newWindow.get_entered_sex()
            newAge = self.newWindow.get_entered_Age()
            newMajor = self.newWindow.get_entered_Major()
            newPhoto = self.newWindow.get_entered_Photo()
            self.Studentinfo = Studentinfo(self.db, self.cursor, newID, newName, newSex, newAge, newMajor, newPhoto)
            self.Studentinfo.show()

    def check_all_prizes(self):
        self.tableWindow = ShowAllTable(self.db, self.cursor, 3, '')
        self.tableWindow.show()
    
    def check_all_punishments(self):
        self.tableWindow = ShowAllTable(self.db, self.cursor, 4, '')
        self.tableWindow.show()

    

    def change_class(self):
        getID = EnterSingleText('修改','课程号')
        if getID.exec():
            # 如果用户点击确认按钮，则获取输入的文本
            oldID = getID.get_entered_text()
            oldinfo = functions.get_course(self.db, self.cursor, oldID)
            if oldinfo == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '课程不存在')
            else:
                self.changeWindow = ChangeClassWindow(self.db, self.cursor, oldinfo)
                if self.changeWindow.exec():
                    newID = self.changeWindow.get_entered_ID()
                    newName = self.changeWindow.get_entered_Name()
                    newCredit = self.changeWindow.get_entered_Credit()
                    functions.change_course(self.db, self.cursor, oldID, 1, newName)
                    functions.change_course(self.db, self.cursor, oldID, 2, newCredit)
                    functions.change_courseid(self.db, self.cursor, oldID, newID)
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '修改成功') #触发的事件时弹出会话框

    def change_student(self):
        getID = EnterSingleText('修改','学生的学号')
        if getID.exec():
            # 如果用户点击确认按钮，则获取输入的文本
            oldID = getID.get_entered_text()
            oldinfo = functions.get_student(self.db, self.cursor, oldID)
            if oldinfo == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学生不存在')
            else:
                self.changeWindow = ChangeStudentWindow(self.db, self.cursor, oldinfo)
                if self.changeWindow.exec():
                    newID = self.changeWindow.get_entered_ID()
                    newName = self.changeWindow.get_entered_Name()
                    newSex = self.changeWindow.get_entered_Sex()
                    newAge = self.changeWindow.get_entered_Age()
                    newMajor = self.changeWindow.get_entered_Major()
                    newPhoto = self.changeWindow.get_entered_Photo()
                    functions.change_student(self.db, self.cursor, oldID, 1, newName)
                    functions.change_student(self.db, self.cursor, oldID, 2, newSex)
                    functions.change_student(self.db, self.cursor, oldID, 3, newAge)
                    functions.change_student(self.db, self.cursor, oldID, 4, newMajor)
                    functions.change_student(self.db, self.cursor, oldID, 5, newPhoto)
                    functions.change_studentid(self.db, self.cursor, oldID, newID)
                    widget = QWidget()
                    QMessageBox.information(widget, '信息', '修改成功') #触发的事件时弹出会话框


    def delete_prize_for_student(self):
        self.deleteWindow = DeletePAWindow(self.db, self.cursor, 0)
        if self.deleteWindow.exec():
            newID = self.deleteWindow.get_entered_ID()
            newName = self.deleteWindow.get_entered_Name()
            functions.del_award(self.db, self.cursor, newID, newName)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '删除成功')

    def delete_punish_for_student(self):
        self.deleteWindow = DeletePAWindow(self.db, self.cursor, 1)
        if self.deleteWindow.exec():
            newID = self.deleteWindow.get_entered_ID()
            newName = self.deleteWindow.get_entered_Name()
            functions.del_punish(self.db, self.cursor, newID, newName)
            widget = QWidget()
            QMessageBox.information(widget, '信息', '删除成功')

    def delete_student(self):
        getID = EnterSingleText('删除','学生的学号')
        if getID.exec():
            ID = getID.get_entered_text()
            info = functions.get_student(self.db, self.cursor, ID)
            if info == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '学生不存在')
            else:
                functions.del_student(self.db, self.cursor, ID)
                widget = QWidget()
                QMessageBox.information(widget, '信息', '删除成功') #触发的事件时弹出会话框

    def delete_class(self):
        getID = EnterSingleText('删除','课程号')
        if getID.exec():
            ID = getID.get_entered_text()
            info = functions.get_course(self.db, self.cursor, ID)
            if info == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '课程不存在')
            else:
                functions.del_course(self.db, self.cursor, ID)
                widget = QWidget()
                QMessageBox.information(widget, '信息', '删除成功') #触发的事件时弹出会话框

    def delete_prize(self):
        getID = EnterSingleText('删除','奖项')
        if getID.exec():
            ID = getID.get_entered_text()
            info = functions.get_prize(self.db, self.cursor, ID)
            if info == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '奖项不存在')
            else:
                functions.del_prize(self.db, self.cursor, ID)
                widget = QWidget()
                QMessageBox.information(widget, '信息', '删除成功') #触发的事件时弹出会话框

    def delete_punishment(self):
        getID = EnterSingleText('删除','惩罚')
        if getID.exec():
            ID = getID.get_entered_text()
            info = functions.get_punishment(self.db, self.cursor, ID)
            if info == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '惩罚不存在')
            else:
                functions.del_punishment(self.db, self.cursor, ID)
                widget = QWidget()
                QMessageBox.information(widget, '信息', '删除成功') #触发的事件时弹出会话框


    def delete_score(self):
        self.newWindow = DeleteScoreWindow(self.db, self.cursor)
        if self.newWindow.exec():
            newsID = self.newWindow.get_entered_sid()
            newcID = self.newWindow.get_entered_cid()
            oldinfo = functions.get_student_score(self.db, self.cursor, newsID, newcID)
            if oldinfo == None:
                widget = QWidget()
                QMessageBox.information(widget, '信息', '成绩不存在')
            else:
                functions.del_score(self.db, self.cursor, newsID, newcID)
                widget = QWidget()
                QMessageBox.information(widget, '信息', '删除成功') #触发的事件时弹出会话框




    def confirm_reset_db(self):
        reply = QMessageBox.question(self, '确认', '你确定要重置数据库吗?',
                                     QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No, 
                                     QMessageBox.StandardButton.No)
        if reply == QMessageBox.StandardButton.Yes:
            self.reset_db()

    def confirm_update_func(self):
        reply = QMessageBox.question(self, '确认', '你确定要重置函数等吗?', 
                                     QMessageBox.StandardButton.Yes | QMessageBox.StandardButton.No, 
                                     QMessageBox.StandardButton.No)
        if reply == QMessageBox.StandardButton.Yes:
            self.update_func()
    
    def reset_db(self):
        inittable.init_table(self.db, self.cursor)
        db_functions.db_functions(self.db, self.cursor)
        db_procedures.db_procedures(self.db, self.cursor)
        db_triggers.db_triggers(self.db, self.cursor)
        widget = QWidget()
        QMessageBox.information(widget, '信息', '成功重置数据库') #触发的事件时弹出会话框

    def update_func(self):
        db_functions.db_functions(self.db, self.cursor)
        db_procedures.db_procedures(self.db, self.cursor)
        db_triggers.db_triggers(self.db, self.cursor)
        widget = QWidget()
        QMessageBox.information(widget, '信息', '成功重置了自定义的函数，触发器，存储过程') #触发的事件时弹出会话框