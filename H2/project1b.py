import numpy as np
import sys
import matplotlib.pylab as mpl
import time

#take input for matrix size
n = int(sys.argv[1])

#define steplength
h = 1/float(n-1)

#define arrays for tridiagonal matrix and x-values
a = np.zeros(n+1)							#original diagonal elements
a.fill(2)
atilde = np.zeros(n+1)										#final diagonal elements
b = np.zeros(n+1)							#first lower diagonal elements
b.fill(-1)
c = np.zeros(n+1)							#first upper diagonal elements
c.fill(-1)
x = np.linspace(0, 1, n+1)

#array for solution
u = np.zeros(n+1)

#analytical solution
analytic = 1 - (1-np.exp(-10))*x-np.exp(-10*x)

#array for values of our function
f = h**2*100*np.exp(-10*x)
ftildepre = np.zeros(n+1)

#define the function that allows us to calculate the new diagonal elements
def atildei(a_i, c, b, atildeprev):
	return a_i - (c*b)/float(atildeprev)


#define the function that allows us to calculate the new functional elements
def ftildei(f_i, fprev, c, atildeprev):
	if atildeprev != 0:
		return f_i - (fprev*c)/float(atildeprev)
	else:
		return f_i
#define the function that gives the solution to the problem
def sol(ftildeprev, b, unext, atilde):
	if b != 0:
		return (ftildeprev - b*unext)/float(atilde)
	else:
		#since u(0) = 0 anyways
		return 0
#set initial values
atilde[0] = a[0]
b[-1] = 0
c[0] = 0
u[0] = u[-1] = 0



#for loop to solve 
start = time.clock()
for i in range(n):
	atilde[i+1] = atildei(a[i+1], c[i], b[i], atilde[i])
	ftildepre[i+1] = ftildei(f[i+1], ftildepre[i], c[i], atilde[i])

for i in range(n-1, -1, -1):
	u[i] = sol(ftildepre[i], b[i], u[i+1], atilde[i])
stop = time.clock()

print stop - start


mpl.plot(x, f, "--")
mpl.hold("On")
mpl.plot(x, u)
mpl.plot(x,analytic, "r--")
mpl.show()