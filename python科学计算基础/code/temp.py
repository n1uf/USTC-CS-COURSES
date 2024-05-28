# -*- coding: utf-8 -*-
"""
Created on Wed Mar  9 21:10:27 2022

@author: niu
"""

import matplotlib.pyplot as plt
import numpy as np
x = np.linspace(0, 4, 101)
y = np.exp(-x) * np.sin(np.pi * x)
plt.plot(x, y)
plt.title('TEST')
plt.savefig('tmp.png')
plt.show()