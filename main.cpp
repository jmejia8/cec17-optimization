#include "optim_mass.hpp"


double *OShift,*M,*y,*z,*x_bound;
int ini_flag=0,n_flag,func_flag,*SS;


int run(int myf, int dimension, int exec) 
{
	int i,j,k,n,m,func_num,iter;
	double *f,*x;
	FILE *fpt;
	int evals = 0;

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
	evaluateSperms(x, f, m, n, func_num, &evals);

	optim(x, f, m, n, func_num, iter, exec, &evals);
	printf(" evals = %d\n", evals);

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

	int dimension = 50;
	int num_runs = 1;
	
	int exec, i;

	char dirname[256];
	
	sprintf(dirname, "experiments/d%d/", dimension);
	createDirectory(dirname);

	// function number
	for (i = 1; i <= 30; ++i) {
		sprintf(dirname, "experiments/d%d/fun%d", dimension, i);
		createDirectory(dirname);
		
		// execution number
		for (exec = 0; exec < num_runs; ++exec) {
			sprintf(dirname, "experiments/d%d/fun%d/run%d/", dimension, i, exec);
			createDirectory(dirname);
		
			printf("run = %2d  fun = %2d dimension = %2d  ", exec, i, dimension);
			run(i, dimension, exec);
			
		}

	}

	return 0;
}