import numpy as np
import pybind_example

A = [0,1,2,3,4,5]
B = pybind_example.multiply(A)

print('input list = ',A)
print('output     = ',B)

A = np.arange(10)
B = pybind_example.multiply(A)

print('input list = ',A)
print('output     = ',B)