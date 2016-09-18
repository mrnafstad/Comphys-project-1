#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Calculates f(x)
double f_func(double x){
	return 100.0*exp(-10.0*x);
}

// Calculates the analytical solution u(x)
double exact(double x){
	return 1.0 - (1 -exp(-10))*x - exp(-10*x);
}

int main(int argc, char* argv[]){
	int n;
	double h, *x, *a, *b, *c, *a_tilde, *f, *f_tilde, *u, *v, tot_time;
	clock_t start, finish;

	n = atoi(argv[1]); //length of arrays
	h = 1.0/(n -1);    // steplength
	
	x = new double [n];  a = new double [n];  b = new double [n];
	c = new double [n];  a_tilde = new double [n];  f = new double [n];
	f_tilde = new double [n];  u = new double [n];  v = new double [n];

	// Fills arrays with known values
	for(int i = 0; i <= n-1; i++){
		x[i] = h*i;
		a[i] = 2;
		b[i] = -1;
		c[i] = -1;
	}
	
	// Sets all initial conditions
	b[n-1] = 0;
	c[0] = 0;
	

	a_tilde[0] = a[0];
	f[0] = f_func(x[0])*pow(h,2);
	f_tilde[0] = f[0];

	v[n-1] = 0;
	u[0] = 0;


	start = clock();  // starting timer

	// Calulating all intermediate values 
	for(int i = 1; i<= n-1; i++){
		f[i] = f_func(x[i])*pow(h, 2);
		a_tilde[i] = a[i] - b[i-1]*c[i-1]/a_tilde[i-1];
		f_tilde[i] = f[i] - f_tilde[i-1]*c[i-1]/a_tilde[i-1];
		u[i] = exact(x[i]); 
	}

	//Calculates the numerical approximation
	for(int i = n-2; i >= 0; i--){
		v[i] = (f_tilde[i] - b[i]*v[i+1])/a_tilde[i];
	}

	finish = clock(); // Stopping timer

	tot_time = ((double)(finish - start)/CLOCKS_PER_SEC);

	//Making sure these values are the initial conditions
	u[n-1] = 0;
	v[0] = 0;
	
	printf("Processing time: %f seconds.", tot_time);

	delete [] x; delete [] a; delete [] b; delete [] c;
	delete [] a_tilde; delete [] f; delete [] f_tilde;
	delete [] u; delete [] v;
	

	return 0;
}

//terminal> P1b 10000
//Processing time: 0.002000 seconds.

//terminal> P1b 100000
//Processing time: 0.015000 seconds.

//terminal> P1b 1000000
//Processing time: 0.147000 seconds.