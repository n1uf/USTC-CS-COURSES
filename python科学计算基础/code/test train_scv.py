# -*- coding: utf-8 -*-
"""
Created on Thu Apr 28 14:19:32 2022

@author: niu
"""

import pandas as pd

train = pd.read_csv("C:\\Users\\niu\\desktop\\研讨课\\Bike-Sharing-Dataset\\train.csv", sep = ',', parse_dates = ['starttime'])

train.head()