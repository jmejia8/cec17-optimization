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
#include <sys/types.h>
#include <sys/stat.h>

#include "cec17_test_func.cpp"
#include "tools.hpp"
#include "optim_mass.hpp"


// void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int run(int myf, int dimension, int exec) 
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


	optim(x, f, m, n, func_num, iter, exec);


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

	int dimension = 10;
	
	int exec, i;

	char dirname[256];
	
	sprintf(dirname, "experiments/d%d/", dimension);
	createDirectory(dirname);

	// function number
	for (i = 1; i <= 30; ++i) {
		sprintf(dirname, "experiments/d%d/fun%d", dimension, i);
		createDirectory(dirname);
		
		// execution number
		for (exec = 0; exec < 51; ++exec) {
			sprintf(dirname, "experiments/d%d/fun%d/run%d/", dimension, i, exec);
			createDirectory(dirname);
		
			printf("Function = %d \t dimension = %d \t run = %d\n", i, dimension, exec);
			run(i, dimension, exec);
			evals = 0;
			
		}

	}

	return 0;
}