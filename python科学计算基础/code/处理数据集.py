# -*- coding: utf-8 -*-
"""
Created on Sun May 22 15:28:09 2022

@author: niu
"""

#常规操作，首先导入各种需要的包
import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
from math import radians,cos,sin,asin,sqrt
import geohash

#读取训练集和测试集
train = pd.read_csv("C:\\Users\\niu\\desktop\\研讨课\\Bike-Sharing-Dataset\\train.csv", sep = ',', parse_dates = ['starttime'])
test = pd.read_csv("C:\\Users\\niu\\desktop\\研讨课\\Bike-Sharing-Dataset\\test.csv", sep = ',', parse_dates = ['starttime'])

tuple a
a = geohash.decode(train.geohashed_start_loc[i])