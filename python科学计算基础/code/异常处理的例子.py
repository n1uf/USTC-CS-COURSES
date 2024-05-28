#  异常处理
def gcd(a, b):
    """ compute the greatest common divisor of a and b using repeated subtractions """
    while a != b:
        if a > b:
           a -= b;
        else:
            b -= a;
    return a

class InputRangeError(Exception):
    """Raised when an input is not in suitable range

    Attributes:
       message -- explanation of suitable range
    """
    def __init__(self, message):
        self.message = message
        
import sys
try:
    x = int(sys.argv[1])
    y = int(sys.argv[2])
    if x < 0 or y < 0:
        raise InputRangeError('Each integer should be positive')
except IndexError:
    print('Two arguments must be supplied on the command line')
except ValueError:
    print('Each argument should be an integer.')
else:
    print ('The greatest common divisor of %d and %d is %d' %\
           (x, y, gcd(x, y)))
finally:
    print("executing finally clause")
    
    
