import numpy as np
import sys

n = int(sys.argv[1])

a = np.zeros(n)
b = np.zeros(n)
c = np.zeros(n)
x = np.linspace(0, 1, n)

f = 100*np.exp(-10*x)

def atildei(a_i, c, b, atildeprev):
	return a_i - (c*b)/float(atildeprev)

def ftildei(f_i, fprev, c, atildeprev):
	return f_i - fprev*c/float(atildeprev)

def sol(ftildeprev, b, unext, atilde):
	return (ftildeprev - b*unext)/float(atilde)



