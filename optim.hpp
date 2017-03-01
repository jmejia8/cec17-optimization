// Porcentaje de la longitud del paso por interación
#define STEP_P 0.1
#define H 0.0001

double partial (double* x, int sperm, int xi, int n, int func_num){
	int i, m = 2;
	double* x_tmp = allocSperms(m, n);
	double* f_tmp = allocSperms(m, 1);

	int a = sperm*n;

	for (i = 0; i < n; ++i){
		x_tmp[i] = x[a + i];
		x_tmp[n + i] = x_tmp[i];
	}

	x_tmp[n + xi] += H;

	cec17_test_func(x_tmp, f_tmp, n, m, func_num);

	double df = (f_tmp[0] - f_tmp[1]) / H;

	free(x_tmp);
	free(f_tmp);

	return df;

}

void nextPosition (double* x, int sperm, int egg, int n, int func_num){
	int i; double df;

	for (i = 0; i < n; ++i) {
		df = partial(x, sperm, i, n, func_num);

		x[sperm + i] += STEP_P * df  -  (x[egg] - x[i]);
	}

}

int iterate(double* x, double* f, int egg, int m, int n, int func_num){
	int i;
	for (i = 0; i < m; ++i) {

		nextPosition(x, i*n, egg*n, n, func_num);
		cec17_test_func(x, f, n, m, func_num);
		
		if (egg != i && f[i] < f[egg])
			egg = i;
	}

	return egg;
}

void optim(double* x, double* f, int m,  int n, int func_num, int iter) {
	int i, egg = 0;

	int old = -1;
	for (i = 0; i < iter; ++i) {
		egg = iterate(x, f, egg, m, n, func_num);
		if (egg != old) {
			printf("%d %lf \n", egg, f[egg]);
		}

		old = egg;
	}

	printf(">---->>>>>>>>---------->>>>>>\n");
	for (int i = 0; i < m; ++i) {
		printf("%lf\n", f[i]);
	}

}