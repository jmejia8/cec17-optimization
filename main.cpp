/*
  CEC17 Test Function Suite for Single Objective Optimization
  Noor Awad (email: noor0029@ntu.edu.sg) 
  Dec. 12th 2013
*/

// #include <WINDOWS.H>    
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "cec17_test_func.cpp"
#include "tools.hpp"
#include "optim_mass.hpp"


// void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int run(int myf, int dimension) 
{
	int i,j,k,n,m,func_num,iter;
	double *f,*x;
	FILE *fpt;

	// dimension
	n = dimension;

	// population
	m = SUB_POPULATION * n;

	// iteration number
	iter = 10000 * n;

	// function number
	func_num = myf;

	x = allocSperms(m, n);
	f = allocSperms(m, 1);

	setSpermsPosition(x, m, n);
	evaluateSperms(x, f, m, n, func_num);

	// for (int i = 0; i < m; ++i)
	// {
	// 	printf("%lg\n ", f[i]);
	// }

	// printf("\n");
	// exit(0);

	// return 0;
	optim(x, f, m, n, func_num, iter);
	// printSperms(x, f, 10, n);
	// show_best(x, f, m, n);


	free(x);
	free(f);
	// free(y);
	// free(z);
	// free(M);
	// free(OShift);
	// free(x_bound);

	return 0;
}



int main(int argc, char const *argv[])
{
	srand(time(NULL));

	int dimension = 2;
	int i;
	for (int i = 1; i <= 30; ++i) {
		printf("Function = %d \t dimension = %d\n", i, dimension);
		run(i, dimension);
		evals = 0;
		
	}
	return 0;
}