#ifndef RADIUOS
	#define RADIUOS 100
#endif

FILE* divs;


double randm() {
    return ( (double) rand() ) / ( (double) RAND_MAX ) ;
}

int randint() {
    return rand();
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

double minimum(double* list, int list_size) {
	int i;
	double M = list[0];
	for ( i = 1; i < list_size; ++i) {
		if (list[i] < M)
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

double distance(double* population, int pop_size, int dimension, int x1, int x2){
	double d = 0.0;
	int i, j;

	x1 *= dimension;
	x2 *= dimension;

	for (int i = 0; i < dimension; ++i) {
		d += pow(population[x1 + i] - population[x2 + i], 2);
	}

	return sqrt(d);
}

double diversity(double* x, int pop_size, int dimension){
	double LP = sqrt(dimension) * 2 * RADIUOS * pop_size;
	int i;


	double* xmean = allocSperms(dimension, 1);
	zeros(xmean, dimension);

	for (int i = 0; i < pop_size; ++i) {
		int index = i * dimension;
		for (int j = 0; j < dimension; ++j) {
			// index += j;
			xmean[j] += x[index + j] ;
		}
	}

	for (int i = 0; i < dimension; ++i){
		xmean[i] /= pop_size;
		// printf("%lf, ", xmean[i]);
	}

	// printf("\ndmean = %lf\n", mean(xmean, dimension));

	// printf("\n====================\n");



	double d = 0;

	for (int i = 0; i < pop_size; ++i) {
		double distance = 0;
		int index = i * dimension;
		for (int j = 0; j < dimension; ++j) {
			// index  j;
			distance +=  pow(x[index + j] - xmean[j], 2) ;
		}

		d += sqrt(distance);

		// printf("\n>>> dist%lf\n", sqrt(distance));
	}

	// printf("\n>>> dist ===  %lf\n", d);


	free(xmean);

	return  d / pop_size;

}

double DALL(double* x, int pop_size, int dimension){
	double d = 0.0;
	double LP = sqrt(dimension) * 2 * RADIUOS * pop_size;

	int i, j;

	for (int i = 0; i < pop_size; ++i) {
		for (int j = 0; j < pop_size; ++j) {
			d += distance(x, pop_size, dimension, i, j);
		}
	}

	return d /(pop_size * pop_size);
}