#!/usr/bin/env python2
#https://matthew-brett.github.io/teaching/floating_error.html

import numpy as np
from math import log10, floor

x = -0.1234             # a number with greater precision than format allows
p = 3                   # number of digits in mantissa
x1 = abs(x)             # 0.1234
e1 = log10(x1)          # -0.9086848403027772
exponent = floor(e1)    # -1
m1 = x / (10 ** e1)     # -1.234
mantissa = round(m1, p-1) # -1.23

print mantissa

print np.finfo(np.float64).eps == 2**(1-53)
