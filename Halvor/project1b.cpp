using namespace std;
#include <cmath>
#include <iostream>
#include <time.h>

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
	n = atof(argv[1])
	vector<double> x = linspace(0, 1, n);
	new<double> 
}
