# -*- coding: utf-8 -*-
"""
Created on Sun May 22 17:32:37 2022

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

#取样
train = train.sample(frac=0.1)

def _processData(df):
    #将starttime 分成weekday,day,hour三类，方便后续不同时间段数据展示
    df['weekday'] = df['starttime'].apply(lambda s : s.weekday())
    df['day'] = df['starttime'].apply(lambda s : str(s)[:10])
    df['hour'] = df['starttime'].apply(lambda s : s.hour)
    print('时间处理完成')
    
    #将geohash字符串反编码，方便后续计算骑行距离
    df['start_lat_lng'] = df['geohashed_start_loc'].apply(lambda s : geohash.decode(s))
    df['end_lat_lng'] = df['geohashed_end_loc'].apply(lambda s : geohash.decode(s))
    df['start_neighbors'] = df["geohashed_start_loc"].apply(lambda s : geohash.neighbors(s))
    
    #原数据中的geohash字符串是g7，现在转成g6
    df['geohashed_start_loc_6'] = df['geohashed_start_loc'].apply(lambda s : s[:6])
    df['geohashed_end_loc_6'] = df['geohashed_end_loc'].apply(lambda s : s[:6])
    df['start_neighbors_6'] = df["geohashed_start_loc_6"].apply(lambda s : geohash.neighbors(s))
    print('Geohash处理完成')
    
    #判断目的地是否在neighbors
    def inGeohash(start_geohash, end_geohash, names):
        names.append(start_geohash)
        if end_geohash in names:
            return 1
        else:
            return 0
    df['inside'] = df.apply(lambda s : inGeohash(s['geohashed_start_loc'],s['geohashed_end_loc'],s['start_neighbors']), axis = 1)
    df['inside_6'] = df.apply(lambda s : inGeohash(s['geohashed_start_loc_6'],s['geohashed_end_loc_6'],s['start_neighbors_6']), axis = 1)
    print("Geohash近邻判断处理完成")
    
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

def analysis_1(data, target):
    g1 = data.groupby(['day',target])
    group_data = g1.agg({"orderid":"count","userid":"nunique","bikeid":"nunique"}).reset_index()
    for each in ["orderid","userid","bikeid"]:
        sns.distplot(group_data[each])
        plt.show()
    return group_data




# 两点距离
def distance(e1, e2):
    return np.sqrt((e1[0]-e2[0])**2+(e1[1]-e2[1])**2)

# 集合中心
def means(arr):
    return np.array([np.mean([e[0] for e in arr]), np.mean([e[1] for e in arr])])

# arr中距离a最远的元素，用于初始化聚类中心
def farthest(k_arr, arr):
    f = [0, 0]
    max_d = 0
    for e in arr:
        d = 0
        for i in range(k_arr.__len__()):
            d = d + np.sqrt(distance(k_arr[i], e))
        if d > max_d:
            max_d = d
            f = e
    return f

# arr中距离a最近的元素，用于聚类
def closest(a, arr):
    c = arr[1]
    min_d = distance(a, arr[1])
    arr = arr[1:]
    for e in arr:
        d = distance(a, e)
        if d < min_d:
            min_d = d
            c = e
    return c


if __name__=="__main__":
    ## 生成二维随机坐标
    ## arr形如：[ (x1, y1), (x2, y2), (x3, y3) ... ]
    arr = np.random.randint(100, size=(100, 1, 2))[:, 0, :]
    print(arr)

    ## 初始化聚类中心和聚类容器
    m = 5
    r = np.random.randint(arr.__len__() - 1)
    k_arr = np.array([arr[r]])
    cla_arr = [[]]
    for i in range(m-1):
        k = farthest(k_arr, arr)
        k_arr = np.concatenate([k_arr, np.array([k])])
        cla_arr.append([])

    ## 迭代聚类
    n = 100
    cla_temp = cla_arr
    for i in range(n):    # 迭代n次
        for e in arr:    # 把集合里每一个元素聚到最近的类
            ki = 0        # 假定距离第一个中心最近
            min_d = distance(e, k_arr[ki])
            for j in range(1, k_arr.__len__()):
                if distance(e, k_arr[j]) < min_d:    # 找到更近的聚类中心
                    min_d = distance(e, k_arr[j])
                    ki = j
            cla_temp[ki].append(e)
        # 迭代更新聚类中心
        for k in range(k_arr.__len__()):
            if n - 1 == i:
                break
            k_arr[k] = means(cla_temp[k])
            cla_temp[k] = []

    ## 可视化展示
    col = ['HotPink', 'Aqua', 'Chartreuse', 'yellow', 'LightSalmon']
    for i in range(m):
        plt.scatter(k_arr[i][0], k_arr[i][1], linewidth=10, color=col[i])
        plt.scatter([e[0] for e in cla_temp[i]], [e[1] for e in cla_temp[i]], color=col[i])
    plt.show()
print(k_arr)
