#  Polynomial类
class Polynomial(object):
    def __init__(self, poly):
        self.poly = {}
        for power in poly:
            if abs(poly[power]) > tol: self.poly[power] = poly[power] #不是0的项可以正常输出

    def __call__(self, x): #求函数值
        value = 0.0 #初始值
        for power in self.poly: value += self.poly[power]*x**power #遍历
        return value

    def __add__(self, other): #多项式加法
        sum = self.poly.copy()   #  print (id(sum), id(self.poly))
        for power in other.poly: #遍历另一个多项式
            if power in sum: #指数相同时
                sum[power] += other.poly[power] #相加
            else: #指数不同
                sum[power] = other.poly[power] #直接赋值
        return Polynomial(sum) #返回多项式sum

    def __mul__(self, other): #多项式乘法
        sum = {}
        for self_power in self.poly:
            for other_power in other.poly:
                sum[self_power + other_power] = \
                    self.poly[self_power] * other.poly[other_power]
        return Polynomial(sum)

    def __str__(self):
        s = ''
        for power in sorted(self.poly):
            s += ' + %g*x^%d' % (self.poly[power], power) #百分号用于套用格式输出
        #各种�
况的替换
        s = s.replace('+ -', '- ') 
        s = s.replace('x^0', '1')
        s = s.replace(' 1*', ' ')
        s = s.replace('x^1 ', 'x ')
        # s = s.replace('x^1', 'x') replaces x^100 by x^00
        if s[0:3] == ' + ':  # remove initial +
            s = s[3:]
        if s[0:3] == ' - ':  # fix spaces for initial -
            s = '-' + s[3:]
        return s

tol = 1E-15
p1 = Polynomial({0: -1, 2: 1, 7: 3})
print (p1)      #  -1 + x^2 + 3*x^7
p2 = Polynomial({0: 1, 2: -1, 5: -2, 3: 4})
print (p2)      #  1 - x^2 + 4*x^3 - 2*x^5
p3 = p1 + p2
print (p3)      #  4*x^3 - 2*x^5 + 3*x^7
p4 = p1 * p2
print (p4)
#  -1 + x^2 - 4*x^3 - x^4 + 4*x^5 + 3*x^7 - 3*x^9 + 12*x^10 - 6*x^12
print (p4(5))   #  -1353269851.0

#  