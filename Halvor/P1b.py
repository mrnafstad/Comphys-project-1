from matplotlib.pylab import *
from numpy import *
import sys
'''
def a_temp(a, b_min, c_min, a_temp_min):
	return a - b_min*c_min/a_temp_min

def f(v):
	return 100*exp(-10.0*v)

def v(f_temp, b, v_plus, a_temp):
	return (f_temp - b*v_plus)/a_temp
'''

n = int(sys.argv[1])
h = 1.0/(n - 1)

x = linspace(0, 1, n)

a = zeros(n); a.fill(2)
b = zeros(n); b.fill(-1); b[-1] = 0
c = zeros(n); c.fill(-1); c[0] = 0
a_temp = zeros(n); a_temp[0] = a[0]
f = zeros(n); f[0] = 100
f_temp = zeros(n); f_temp[0] = f[0]

v = zeros(n); v[-1] = 0
u = zeros(n); u[0] = 0

for i in range(1,n):
	f[i] = 100*exp(-10.0*x[i])
	a_temp[i] = a[i] - b[i-1]*c[i-1]/a_temp[i-1]
	f_temp[i] = f[i] - f_temp[i-1]*c[i-1]/a[i-1]
	u[i] = 1 - (1 - exp(-10))*x[i] - exp(-10*x[i])

for i in range(n-2, -1, -1):
	v[i] = (f_temp[i] - b[i]*v[i+1])/a_temp[i]

u[-1] = 0
v[0] = 0

plot(x, v)
hold('on')
plot(x, u)
legend(['Computed(v)', 'Exact(u)'])
show()








