#  Complex¿‡
from math import sqrt
tol = 1e-15

class Complex(object):
    def __init__(self, real, imag=0.0):
        self.real = real; self.imag = imag

    def __add__(self, other):
        if isinstance(other, (float,int)): other = Complex(other)
        elif not (hasattr(other, 'real') and hasattr(other, 'imag')):
            raise TypeError('other must have real and imag attr.')
        return Complex(self.real + other.real, self.imag + other.imag)

    def __radd__(self, other):   #  defines other + self
        return self.__add__(other)

    def __sub__(self, other):
        if isinstance(other, (float,int)): other = Complex(other)
        elif not (hasattr(other, 'real') and hasattr(other, 'imag')):
            raise TypeError('other must have real and imag attr.')
        return Complex(self.real - other.real, self.imag - other.imag)

    def __rsub__(self, other):   #  defines other - self
        if isinstance(other, (float,int)): other = Complex(other)
        elif not (hasattr(other, 'real') and hasattr(other, 'imag')):
            raise TypeError('other must have real and imag attr.')
        return other.__sub__(self)

    def __mul__(self, other):
        return Complex(self.real*other.real - self.imag*other.imag,
                       self.imag*other.real + self.real*other.imag)
    def __rmul__(self, other):   #  defines other + self
        return self.__mul__(other)

    def __truediv__(self, other):
        if isinstance(other, (float,int)): other = Complex(other)
        elif not (hasattr(other, 'real') and hasattr(other, 'imag')):
            raise TypeError('other must have real and imag attr.')
        ar, ai, br, bi = self.real, self.imag, other.real, other.imag
        r = float(br*br + bi*bi)
        return Complex((ar*br+ai*bi)/r, (ai*br-ar*bi)/r)

    def __rtruediv__(self, other):   #  defines other / self
        if isinstance(other, (float,int)): other = Complex(other)
        elif not (hasattr(other, 'real') and hasattr(other, 'imag')):
            raise TypeError('other must have real and imag attr.')
        return other.__truediv__(self)

    def __abs__(self):
        return sqrt(self.real*self.real + self.imag*self.imag)

    def __neg__(self): return Complex(-self.real, -self.imag)

    def __eq__(self, other):
        return abs(self.real-other.real) < tol and abs(self.imag-other.imag) < tol

    def __ne__(self, other): return not self.__eq__(other)

    def __str__(self): return '(%g, %g)' % (self.real, self.imag)

    def __repr__(self): return 'Complex' + str(self)

    def __pow__(self, power):
        raise NotImplementedError('pow is not yet implemented')

    def _illegal(self, op):
        print ('illegal operation "%s" for complex numbers' % op)

    def __gt__(self, other):  self._illegal('>')
    def __ge__(self, other):  self._illegal('>=')
    def __lt__(self, other):  self._illegal('<')
    def __le__(self, other):  self._illegal('<=')

u = Complex(2,-3); v = Complex(1, -4)
print (u + v, u - v, u * v,     u / v)
#     (3, -7) (1, 1) (-10, -11) (0.823529, 0.294118)
print (4 + v, 4 - v, 4 * v,   4 / v)
#     (5, -4) (3, 4) (4, -16) (0.235294, 0.941176)
print (u > v)
# illegal operation ">" for complex numbers
print (u ** 3)
# NotImplementedError: pow is not yet implemented
  
