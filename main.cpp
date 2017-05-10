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


int main()
{
	int i,j,k,n,m,func_num,iter;
	double *f,*x;
	FILE *fpt;

	// population
	m = 100;

	// dimension
	n = 30;

	// iteration number
	iter = 10000 * n;

	// function number
	func_num = 1;

	x = allocSperms(m, n);
	f = allocSperms(m, 1);

	setSpermsPosition(x, m, n);
	evaluateSperms(x, f, m, n, func_num);

	printf("inicia lo chido\n");
	optim(x, f, m, n, func_num, iter);
	// printSperms(x, f, 10, n);

	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);

	return 0;
}


