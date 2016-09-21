from matplotlib.pylab import *
from numpy import *
import sys
import time

n = int(sys.argv[1])
h = 1.0/(n - 1)

x = linspace(0, 1, n)

a = 2.0
#b = -1.0     
#c = -1.0
a_temp = zeros(n);  a_temp[0] = a
f = zeros(n);       f[0] = 100*h**2
f_temp = zeros(n);  f_temp[0] = f[0]

v = zeros(n); v[-1] = 0
u = zeros(n); u[0] = 0

time_start = time.clock()

for i in range(1,n):
	f[i] = 100*exp(-10.0*x[i])*h**2
	a_temp[i] = (i+1.0)/i
	f_temp[i] = f[i] + f_temp[i-1]/a_temp[i-1]
	u[i] = 1 - (1 - exp(-10))*x[i] - exp(-10*x[i])

for i in range(n-2, -1, -1):
	v[i] = (f_temp[i] + v[i+1])/a_temp[i]

time_stop = time.clock()

print (time_stop - time_start)

u[-1] = 0
v[0] = 0

plot(x, v)
hold('on')
plot(x, u)
legend(['Computed(v)', 'Exact(u)'])
show()
