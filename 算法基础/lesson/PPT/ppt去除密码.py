# 当前目录下pdf的密码都为 clrs
# 去除当前目录下所有pdf的密码


import os
import sys
import time
import pikepdf
import threading
from multiprocessing import Pool
from multiprocessing import cpu_count

def remove_password(file):
    try:
        pdf = pikepdf.open(file, password='clrs', allow_overwriting_input=True)
        pdf.save(file)
        print(f'{file} remove password success')
    except Exception as e:
        print(f'{file} remove password failed')
        print(e)

def main():
    start = time.time()
    files = os.listdir()
    files = [file for file in files if file.endswith('.pdf')]
    print(f'pdf files: {files}')
    pool = Pool(cpu_count())
    pool.map(remove_password, files)
    pool.close()
    pool.join()
    end = time.time()
    print(f'cost time: {end - start}')

if __name__ == '__main__':
    main()