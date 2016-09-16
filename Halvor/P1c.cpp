#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double f_func(double x){
	return 100.0*exp(-10.0*x);
}

double exact(double x){
	return 1.0 - (1 -exp(-10))*x - exp(-10*x);
}

int main(int argc, char* argv[]){
	int n;
	double h, a, *x, *a_tilde, *f, *f_tilde, *u, *v, tot_time;
	clock_t start, finish;

	n = atoi(argv[1]);
	h = 1.0/(n -1);
	a = 2.0;
	
	x = new double [n];  a_tilde = new double [n];  f = new double [n];
	f_tilde = new double [n];  u = new double [n];  v = new double [n];

	a_tilde[0] = a;
	f[0] = 100*pow(h, 2);
	f_tilde[0] = f[0];

	v[n-1] = 0;
	u[0] = 0;


	for(int i = 0; i <= n-1; i++){
		x[i] = h*i;
	}

	start = clock();

	for(int i = 1; i<= n-1; i++){
		f[i] = f_func(x[i])*pow(h, 2);
		a_tilde[i] = (i + 1.0)/(double)i;
		f_tilde[i] = f[i] + f_tilde[i-1]/a_tilde[i-1];
		u[i] = exact(x[i]);
	}

	for(int i = n-2; i >= 0; i--){
		v[i] = (f_tilde[i] + v[i+1])/a_tilde[i];
	}

	finish = clock();

	tot_time = ((double)(finish - start)/CLOCKS_PER_SEC);

	u[n-1] = 0;
	v[0] = 0;

	printf("Processing time: %f", tot_time);

	delete [] x; delete [] a_tilde; delete [] f; delete [] f_tilde;
	delete [] u; delete [] v;
	

	return 0;
}