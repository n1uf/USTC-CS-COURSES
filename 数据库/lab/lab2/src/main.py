import sys
import pymysql
from PyQt6.QtWidgets import QPushButton, QMessageBox, QApplication, QWidget
import display
#mysql -u root -p
if __name__ == "__main__":
    app = QApplication(sys.argv)
    # 打开数据库连接
    try:
        db = pymysql.connect(host='localhost', user='root', passwd='nqy1002_', port=3306, autocommit=False, database="student_management")
    except:
        print('连接数据库失败')

    cursor = db.cursor()

    display = display.Main_Window(db, cursor)
    display.show()
    sys.exit(app.exec())