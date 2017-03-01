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
#include "optim.hpp"


// void cec17_test_func(double *, double *,int,int,int);

double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int main()
{
	int i,j,k,n,m,func_num,iter;
	double *f,*x;
	FILE *fpt;
	char FileName[30];

	// population
	m = 100;

	// dimension
	n = 10;

	// iteration number
	iter = 1000;

	x = allocSperms(m, n);
	f = allocSperms(m, 1);

	setSpermsPosition(x, n, m);
	evaluateSperms(x, f, n, m, 1);
	
	optim(x, f, m, n, 1, iter);
	return 0;

	for (i = 0; i < 30; i++)
	{
		func_num=i+1;
		sprintf(FileName, "input_data/shift_data_%d.txt", func_num);
		fpt = fopen(FileName,"r");
		if (fpt==NULL)
		{
			printf("\n Error: Cannot open input file for reading \n");
		}
		
		if (x==NULL)
			printf("\nError: there is insufficient memory available!\n");

		for(k=0;k<n;k++)
		{
				fscanf(fpt,"%lf",&x[k]);
				/*printf("%lf\n",x[k]);*/
		}

		fclose(fpt);

			for (j = 0; j < n; j++)
			{
				x[1*n+j]=0.0;
				/*printf("%lf\n",x[1*n+j]);*/
			}
		
		
		for (k = 0; k < 1; k++)
		{
			cec17_test_func(x, f, n,m,func_num);
			for (j = 0; j < 2; j++)
			{
				printf(" f%d(x[%d]) = %lf,",func_num,j+1,f[j]);
			}
			printf("\n");
		}
	
	}
	free(x);
	free(f);
	free(y);
	free(z);
	free(M);
	free(OShift);
	free(x_bound);

	return 0;
}


