
"""
Created on Fri Mar 18 11:06:49 2022

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

#train采样 frac=0.5随机取样
train = train.sample(frac=0.5)

def _processData(df):
    #将starttime 分成weekday,day,hour三类，方便后续不同时间段数据展示
    df['weekday'] = df['starttime'].apply(lambda s : s.weekday())
    df['day'] = df['starttime'].apply(lambda s : str(s)[:10])
    df['hour'] = df['starttime'].apply(lambda s : s.hour)
    print('时间处理完成！！！')
    
    #将geohash字符串反编码，方便后续计算骑行距离
    df['start_lat_lng'] = df['geohashed_start_loc'].apply(lambda s : geohash.decode(s))
    df['end_lat_lng'] = df['geohashed_end_loc'].apply(lambda s : geohash.decode(s))
    
    #原数据中的geohash字符串是g7，现在转成g6
    df['geohashed_start_loc_6'] = df['geohashed_start_loc'].apply(lambda s : s[:6])
    df['geohashed_end_loc_6'] = df['geohashed_end_loc'].apply(lambda s : s[:6])
    print('Geohash处理完成！！！')
    
    
    #计算起点与终点距离
    def haversine(lon1, lat1, lon2, lat2): 
        """
        Calculate the great circle distance between two points 
        on the earth (specified in decimal degrees)
        """
        lon1, lat1, lon2, lat2 = map(radians, [lon1, lat1, lon2, lat2])
        # haversine公式
        dlon = lon2 - lon1 
        dlat = lat2 - lat1 
        a = sin(dlat/2)**2 + cos(lat1) * cos(lat2) * sin(dlon/2)**2
        c = 2 * asin(sqrt(a)) 
        r = 6371 # 地球平均半径，单位为公里
        return c * r * 1000
    df['start_end_distance'] = df.apply(lambda s : haversine(s['start_lat_lng'][0],s['start_lat_lng'][1],s['end_lat_lng'][0],
                                                             s['end_lat_lng'][1]),axis = 1)
    print("距离计算完成！！！")
    return df

def _timeAnalysis(df):
    #数据包含的天数
    print('数据集包含的天数如下：')
    print(df['day'].unique())
    print('*'*60)
    
    #用户出行小时高峰期
    g1 = df.groupby('hour')
    print(g1['orderid'].count().sort_values(ascending = False))
    print('*'*60)
    
    #周一到周日用车分析
    g1 = df.groupby('weekday')
    print(pd.DataFrame(g1['weekday'].count()))
    print('*'*60)
    
    #周一到周日不同时间的用车分析
    df.loc[(df['weekday'] == 5) | (df['weekday'] == 6), 'isWeekend'] = 1
    df.loc[~(df['weekday'] == 5) | (df['weekday'] == 6), 'isWeekend'] = 0
    g1 = df.groupby(['isWeekend', 'hour'])
    
    #计算工作日以及周末的天数
    g2 = df.groupby(['day', 'weekday'])
    w = 0 #周末天数
    c = 0 #工作日天数
    for i,j in list(g2.groups.keys()):
        if j >= 5:
            w += 1
        else:
            c += 1
    
    temp_df = pd.DataFrame(g1['orderid'].count()).reset_index()
    temp_df.loc[temp_df['isWeekend'] == 0 , 'orderid'] = temp_df['orderid']/c
    temp_df.loc[temp_df['isWeekend'] == 1 , 'orderid'] = temp_df['orderid']/w
    print(temp_df.sort_values(['isWeekend', 'orderid'], ascending = False))
    sns.barplot(x = 'hour', y = 'orderid', hue = 'isWeekend', data = temp_df)
