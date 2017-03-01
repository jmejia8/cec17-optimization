// Porcentaje de la longitud del paso por interación
#define STEP_P 1e-6
#define H 1e-6

double partial (double* x, int sperm, int xi, int n, int func_num){
	int i, m = 2;
	double* x_tmp = allocSperms(m, n);
	double* f_tmp = allocSperms(m, 1);

	int a = sperm;

	for (i = 0; i < n; ++i){
		x_tmp[i] = x[a + i];
		x_tmp[n + i] = x_tmp[i];
	}

	x_tmp[n + xi] += H;

	cec17_test_func(x_tmp, f_tmp, n, m, func_num);

	double df = (f_tmp[0] - f_tmp[1]) / H;
	// printf(">>>> >>> %lf\n", df);

	free(x_tmp);
	free(f_tmp);

	return df;

}

void nextPosition (double* x, int sperm, int egg, int n, int func_num, int iter){
	int i; double df;
	// printf("position %lf\n", x[0]);


	for (i = 0; i < n; ++i) {
		if (x[sperm + i] > 100 || x[sperm + i] < -100)
			continue;

		df = partial(x, sperm, i, n, func_num);

		x[sperm + i] += STEP_P * df;

		// if (iter > 10) {
		// 	x[sperm + i]  += 0.1*(x[egg + i] - x[sperm + i]);
		// }
	}

}

int iterate(double* x, double* f, int egg, int m, int n, int func_num, int iter){
	int i;
	for (i = 0; i < m; ++i) {
		// printf("iter %lf\n", x[0]);
		nextPosition(x, i*n, egg*n, n, func_num, iter);
		cec17_test_func(x, f, n, m, func_num);
		
		if (egg != i && f[i] < f[egg])
			egg = i;
	}

	return egg;
}

void optim(double* x, double* f, int m,  int n, int func_num, int iter) {
	int i, egg = 0;
	int old = -1;

	printf("iter \t egg \t f_val\n");
	printf("---------------------------------------\n");
	for (i = 0; i < iter; ++i) {
		egg = iterate(x, f, egg, m, n, func_num, i);
		if (egg != old) {
			printf("%d \t %d \t %.20lf \n", i, egg, f[egg]);
		}

		old = egg;
	}

	egg *= n;
	printf("\n\n_------------------------------------------\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%lf\n", x[egg + i]);
	}

}