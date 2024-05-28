# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 14:48:54 2022

@author: niu
"""


""" 赋值实验 """
a = 7

b = 10000 * (1.03) ** 5

c = 4.5 - 4.4

import sys; max = sys.float_info.max;max


""" if else语句 """
x = int(input("input an integer "))

y = -x if x < 0 else x

if x < 0:
    y = -x
else:
    y = x

print("absolute value of %d is %d" %(x,y))


""" if elif语句 """
x = int(input("please input the grade "))

grade = 'F'

if x > 90:
    grade = 'A'
elif x > 80:
    grade = 'B'
elif x > 70:
    grade = 'C'
elif x > 60:
    grade = 'D'
elif x > 50:
    grade = 'E'
print("the level is %c" %grade)


"""" for循环 """
lb = 100; ub = 120
for i in range(lb, ub + 1, 2):
    print (i, end = ' ')
    
print()

nums = {25, 18, 19, 365, 12, 78, 59}
for i in nums:
    if i % 3 == 0:
        print(i, end = ' ')
        

