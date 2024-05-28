#  数值微分类
class Diff(object):
    def __init__(self, f, h=1E-5, dfdx_exact=None):
        self.f = f
        self.h = float(h)
        self.exact = dfdx_exact

    def get_error(self, x):
        if self.exact is not None:
            df_numerical = self(x)
            df_exact = self.exact(x)
            return 100 * abs( (df_exact - df_numerical) / df_exact )

class Forward1(Diff):
    def __call__(self, x):
        f, h = self.f, self.h
        return (f(x+h) - f(x))/h

class Backward1(Diff):
    def __call__(self, x):
        f, h = self.f, self.h
        return (f(x) - f(x-h))/h

class Central2(Diff):
    def __call__(self, x):
        f, h = self.f, self.h
        return (f(x+h) - f(x-h))/(2*h)

class Central4(Diff):
    def __call__(self, x):
        f, h = self.f, self.h
        return (4./3)*(f(x+h) - f(x-h))  /(2*h) - \
               (1./3)*(f(x+2*h) - f(x-2*h))/(4*h)

from math import exp, sin
def g(x): return exp(x*sin(x))

def table(f, x, h_values, methods, dfdx=None):
    print ('%-10s' % 'h', end=' ')
    for h in h_values: print ('%-8.2e' % h, end=' ')
    print()
    for method in methods:
        print ('%-10s' % method.__name__, end=' ')
        for h in h_values:
            if dfdx is not None:
                d = method(f, h, dfdx)
                output = d.get_error(x)
            else:
                d = method(f, h)
                output = d(x)
            print ('%-8.4f' % output, end=' ')
        print()

#以下为测试
from math import exp, sin
def g(x): return exp(x*sin(x))

from sympy import Symbol, diff, lambdify, exp, sin
sym_x = Symbol('x'); 
sym_gx = g(sym_x)
sym_dgdx = diff(sym_gx, sym_x)
dgdx = lambdify([sym_x], sym_dgdx) #把符号转换为python可以计算的

table(f=g, x=-0.65, h_values=[10**(-k) for k in range(1, 9)],
      methods=[Forward1, Central2, Central4], dfdx=dgdx)
