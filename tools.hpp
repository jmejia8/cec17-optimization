#ifndef RADIUOS
	#define RADIUOS 100
#endif

int seed = 7;

double randm() {
	srand(time(NULL) + seed );
	seed = rand();
    return (double)seed / (double)RAND_MAX ;
}

int randint() {
	srand(time(NULL) + seed );
	seed = rand();
    return seed;
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

double maximum(double* list, int list_size) {
	int i;
	double M = list[0];
	for ( i = 1; i < list_size; ++i) {
		if (list[i] > M)
			M = list[i];
	}

	return M;
}

void zeros(double* list, int list_size){
	int i;
	for (i = 0; i < list_size; ++i)
		list[i] = 0.0;
}

double mean(double* data, int data_len){
	int i;
	double p = 0.;
	for (int i = 0; i < data_len; ++i)
	{
		p += data[i];
	}

	return p /data_len;
}

void order_desc(int* order, double* data, int data_len){
	// Ordenamiento para remplazo de padres por hijos 
	int i, j;
	for ( i = 0; i < data_len; ++i)
		order[i] = i;

	for (i = 0; i < data_len - 1; ++i) {
		for (j = data_len - 1; j > i; --j) {
			if (data[order[j - 1]] < data[order[j]]){
				int tmp = order[j];
				order[j] = order[j - 1];
				order[j-1] = tmp;
			}
		}
	}
}