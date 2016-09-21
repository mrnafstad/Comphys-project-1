#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "lib.h"

// Calculates f(x)
double f_func(double x){
	return 100.0*exp(-10.0*x);
}

// Calculates the analytical solution u(x)
double exact(double x){
	return 1.0 - (1 -exp(-10))*x - exp(-10*x);
}

int main(int argc, char* argv[]){

	FILE *file;

	// Opens file for writing results
	file = fopen("P1e.txt", "w+");
	fprintf(file, " n     Max relative error      Max epsilon value\n");

	// Iterates over n = 10, 100, 1000
	for(int n = 10; n <= 1000; n = n*10){
		int *indx;
		double h, d, tot_time, eps_max, *eps, *x, *f, *u, **A;
		clock_t start, finish;

		printf("n = %i\n", n);

		h = 1.0/(n -1); // Steplength
		
		x = new double [n];  f = new double [n];
		u = new double [n];  eps = new double [n];

		indx = new int[n];
		A = (double**) matrix(n, n, sizeof(double));

		// Sets all matrix elements to 0
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				A[i][j] = 0.0;
			}
		}

		// Sets initial conditions
		A[0][0] = 2.0; A[0][1] = -1.0;

		f[0] = 100*pow(h, 2);
		u[0] = 0;
		u[n-1] = 0;

		// Generates the x-values
		for(int i = 0; i <= n-1; i++){
			x[i] = h*i;
		}

		// Sets values along the diagonals
		for(int i = 1; i <n-1; i++){
			A[i][i-1] = -1.0;
			A[i][i] = 2.0;
			A[i][i+1] = -1.0;
		}


		A[n-1][n-1] = 2.0; A[n-2][n-1] = -1.0; A[n-1][n-2] = -1.0;


		start = clock(); // Starts timer

		// Calculating all intermediate values
		for(int i = 1; i<= n-1; i++){
			f[i] = f_func(x[i])*pow(h, 2);
			u[i] = exact(x[i]);
		}

		//LU-decomposing the matrix A
		ludcmp(A, n, indx, &d);

		// Solving AX = B of the decomposed matrix A (B = f here)
		lubksb(A, n, indx, f);

		finish = clock();  // Stopping timer

		tot_time = ((double)(finish - start)/CLOCKS_PER_SEC);


		//Calculates the log10 of the relative error (epsilon), and finds the max
		eps_max = -1000.0;  //Starting with a low number which is easily upped
		for(int i = 1; i <= n-2; i++){
			eps[i] = log10(fabs((f[i] - u[i])/u[i]));
			if (eps[i] > eps_max){
				eps_max = eps[i];
			}
		}

		/*
		Writing results to file for plotting in Python
		FILE *fp;

		fp = fopen("eplot.txt", "w+");

		for(int i = 0; i < n; i++){
			fprintf(fp, "%f\n", f[i]);
		}

		fclose(fp);
		*/

		// Writes results to file
		fprintf(file, "10^%d       %f              %f\n", (int)log10(n), (pow(10, eps_max)), eps_max);

		printf("Max relative error: %f\n", pow(10, eps_max));
		printf("Max epsilon value: %f\n", eps_max);


		/* Print the last 10 elements in the solution for comparison
		for(int i = n-10; i < n; i++){
			printf("%f\n", f[i]);
		}
		*/

		printf("Processing time: %f seconds.\n\n", tot_time);

		delete [] x; delete [] f; delete[] indx;
		delete [] u; delete [] eps;

		free_matrix((void **) A);

	}
	
	fclose(file); //Closes the file

	return 0;
}


/*Last 10 elements of the solution array for n = 1000:
terminal> P1e 1000
0.010085
0.009077
0.008068
0.007060
0.006051
0.005043
0.004034
0.003026
0.002017
0.001009
*/
