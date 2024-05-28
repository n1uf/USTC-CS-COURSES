# -*- coding: utf-8 -*-
"""
Created on Thu Mar 10 15:25:11 2022

@author: niu
"""

""" 输出质数 """

import math
list1 = []; list2 = []; list3 = []
lb = 0; ub = 1000
if lb % 2 == 0:
    lb += 1
for i in range(lb ,ub + 1, 2):
    isPrime = True
    for j in range(2, math.ceil(math.sqrt(i)) + 1):
        if i % j == 0:
            isPrime = False
            break
    if isPrime:
        list1.append(i)
print(list1)

for i in list1:
    isPrime = True
    k = 2 ** i - 1
    for j in range(2, math.ceil(math.sqrt(k)) + 1):
        if k % j == 0:
            isPrime = False
            break
    if isPrime:
        list2.append(i)
        list3.append(k)
print(list2)
print(list3)