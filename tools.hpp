#ifndef RADIUOS
	#define RADIUOS 100
#endif

int seed = 7;

double randm() {
	srand(time(NULL) + seed );
	seed = rand();
    return (double)seed / (double)RAND_MAX ;
}


double* allocSperms(int m, int n){
	double* tmp =(double *)malloc(m*n*sizeof(double));

	if (tmp == NULL) {
		printf("No memory\n");
		exit(0);
	}

	return tmp;
}

double setSpermsPosition(double* x, int m, int n){
	int i;
	for (i = 0; i < m*n; ++i)
		x[i] = -RADIUOS + 2*RADIUOS * randm();
}

double evaluateSperms(double* x, double* f, int m, int n, int func_num){
	int i;
	for (i = 0; i < m*n; ++i)
		cec17_test_func(x, f, n, m, func_num);
}

void printSperms(double* x, double* f, int m, int n){
	int i, j;
	for (i = 0; i < m; ++i) {
		printf(">>>>  v = %lf\n", f[i]);
		for (j = 0; j < n; ++j) {
			printf("%lf \t", x[n*i + j]);
		}
		printf("\n=================================================\n");
	}
}