using namespace std;
#include <cmath>
#include <iostream>
#include <time.h>
#include <vector>

//Function for linspace array, last element may not be st
vector<double> linspace(double start, double stop, int length)
{
	double space = (stop - start) / (length-1);

	vector<double> arr(length);

	for ( int i = 0; i < length; i++) {
		arr[i] = start + i * space;
	}
	return arr;
}




int main(int argc, char* argv[])
{
	int n;
	double *a, *b, *c, *v, *u, *exact, h, *atilde, *ftilde;

	n = atof(argv[1]);

	vector<double> x = linspace(0, 1, n);
	a = new double [n];
	b = new double [n];
	c = new double [n];
	u = new double [n];
	v = new double [n];
	exact = new double [n];
	atilde = new double [n];
	ftilde = new double [n];

	h = 1./(n - 1);

	for ( int i = 0; i < n; i++) {
		a[i] = 2;
		b[i] = -1;
		c[i] = -1;
		exact[i] = 1 - (1 - exp(-10))*x[i] - exp(-10*x[i]);
		u[i] = h*h*100*exp(-10*x[i]);

	b[-1] = c[0] = 0;
	v[-1] = v[0] = 0;

	}

}
