from numpy import *
from matplotlib.pylab import *
import sys
import time

def maxerr(exact_i, u_i):
	return sqrt((u_i - exact_i/exact_i)**2)

exponential = int(sys.argv[1])

maxerrarr = np.zeros(exponential)

for j in range(1, exponential + 1):
	n = 10**j
	h = 1./(n-1)

	x = linspace(0, 1, n)
	atilde = zeros(n)
	ftilde = zeros(n)
	u = zeros(n)

	eps = zeros(n)

	atilde[0] = 2.
	ftilde[0] = 100*h**2

	f = 100*exp(-10*x)*h**2
	exact = 1 - (1 - exp(-10))*x - exp(-10*x)

	start = time.clock()
	for i in range(1, n):
		atilde[i] = (i+1.)/float(i)
		ftilde[i] = f[i] + ftilde[i-1]/float(atilde[i-1])

	for i in range(n-2, -1, -1):
		u[i] = (ftilde[i] + u[i+1])/float(atilde[i])
		eps[i] = maxerr(exact[i], u[i])
	stop = time.clock()
	print "-----"*5
	print "Time to calculate for %.0f grid points is %1.3e seconds." % (10**j, stop - start)
	maxerrarr[j-1] = max(eps)
	print "For steplength %1.3e the maximum relative error is %1.3e ." % (h, max(eps))

	plot(x, u)
	hold("On")
	plot(x, exact, "r--")
	xlabel("x")
	ylabel("Functional and second derivative values")
show()

print maxerrarr
