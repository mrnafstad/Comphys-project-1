#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <cstring>
#include "lib.h"
using namespace std;


int main(int argc, char* argv[])
{
	int n, m;
	double ** A;
	n = atoi(argv[1]);
	m = atoi(argv[2]);

	A = new double [n];
	// create our special tridiagonal matrix
	for (int i = 0; i = n-1; i++)
	{
		A = new double [n]
		for ( int j = 0; j = n-1; j++)
		{
			if ( i == j )
			{
				//set diagonal elements
				A[i][j] = 2;
			}
			else if (int fabs( j - i) == int 2)
			{
				//set non-diagonal elements
				A[i][j] = -1;
				A[j][i] = -1;
			}
		}
	}
}