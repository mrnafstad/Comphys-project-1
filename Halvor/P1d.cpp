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

	// Making the result-file ready
	FILE *fp;

	fp = fopen("P1d.txt", "w+");
	fprintf(fp, " n     Max relative error      Max epsilon value\n");

	// Loops over n = 10, 100, ... 10^7
	for(int n = 10; n <= pow(10, 7); n = n*10){

		double h, a, *x, *a_tilde, *f, *f_tilde, *u, *v, *eps, eps_max, max_error, tot_time;
		clock_t start, finish;

		printf("n = %i\n", n);

		h = 1.0/(n -1); //Steplength
		a = 2.0;        // Value along the entire diagonal
		
		x = new double [n];  a_tilde = new double [n];  f = new double [n];
		f_tilde = new double [n];  u = new double [n];  v = new double [n];
		eps = new double [n];

		//Sets all intial conditions
		a_tilde[0] = a;
		f[0] = 100*pow(h, 2);
		f_tilde[0] = f[0];
		eps[0] = eps[n-1] = 0;

		v[n-1] = 0;
		u[0] = 0;

		//generates the x-values
		for(int i = 0; i <= n-1; i++){
			x[i] = h*i;
		}

		start = clock(); // Starts timer

		// Calculates all intermediate values
		for(int i = 1; i<= n-1; i++){
			f[i] = f_func(x[i])*pow(h, 2);
			a_tilde[i] = (i + 1.0)/(double)i;
			f_tilde[i] = f[i] + f_tilde[i-1]/a_tilde[i-1];
			u[i] = exact(x[i]);
		}

		// Calculates the numerical approximation
		for(int i = n-2; i >= 0; i--){
			v[i] = (f_tilde[i] + v[i+1])/a_tilde[i];
		}

		//Calculates the log10 of the relative error (epsilon), and finds the max
		eps_max = -1000.0; 
		for(int i = 1; i <= n-2; i++){
			eps[i] = log10(fabs((v[i] - u[i])/u[i]));
			if (eps[i] > eps_max){
				eps_max = eps[i];
			}
		}

		finish = clock(); // Stopping timer

		tot_time = ((double)(finish - start)/CLOCKS_PER_SEC);

		// Making sure these values are the initial conditions
		u[n-1] = 0;
		v[0] = 0;

		fprintf(fp, "10^%d       %f              %f\n", (int)log10(n), (pow(10, eps_max)), eps_max);

		printf("Max relative error: %f\n", pow(10, eps_max));
		printf("Max epsilon value: %f\n", eps_max);

		printf("Processing time: %f\n\n", tot_time);

		delete [] x; delete [] a_tilde; delete [] f; delete [] f_tilde;
		delete [] u; delete [] v;
	}

	fclose(fp); // Closes file

	return 0;
}