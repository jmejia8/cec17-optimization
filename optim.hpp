// Porcentaje de la longitud del paso por interación
#define C_1		1e-8
#define C_2		1e-2
#define H 		1e-8
// #define HELP	1e-7

int evals = 0;

void myfunc(double *x, double *f, int nx, int mx, int func_num){
	evals++;
	cec17_test_func(x, f, nx, mx, func_num);
}

double partial (double* x, int sperm, int xi, int n, int func_num){
	int i, m = 2;
	double* x_tmp = allocSperms(m, n);
	double* f_tmp = allocSperms(m, 1);

	for (i = 0; i < n; ++i){
		x_tmp[i] = x[sperm + i];
		x_tmp[n + i] = x_tmp[i];
	}

	x_tmp[n + xi] += H;

	myfunc(x_tmp, f_tmp, n, m, func_num);

	double df = (f_tmp[0] - f_tmp[1]) / H;

	free(x_tmp);
	free(f_tmp);

	return df;

}

void nextPosition (double* x, int sperm, int egg, int n, int func_num, int iter){
	int i; double df, w;
	// printf("position %lf\n", x[0]);

	for (i = 0; i < n; ++i) {

		df = partial(x, sperm, i, n, func_num);
		// w = C_1 * df + 
		x[sperm + i] += C_1 * df + randm() * 0.0009;
		x[sperm + i] += C_2 * (x[egg + i] - x[sperm + i]);


		if (x[sperm + i] > 100 || x[sperm + i] < -100){
			x[sperm + i] = -RADIUOS + 2*RADIUOS * randm();
		}
	}

}

int iterate(double* x, double* f, int egg, int old, int m, int n, int func_num, int iter){
	int i;
	for (i = 0; i < m; ++i) {
		// printf("iter %lf\n", x[0]);
		nextPosition(x, i*n, egg*n, n, func_num, iter);
		myfunc(x, f, n, m, func_num);
		
		if (egg != i && f[i] < f[egg])
			egg = i;
	}

	return egg;
}

void optim(double* x, double* f, int m,  int n, int func_num, int iter) {
	int i, j, egg, old;
	double p = 0;

	for (i = 0; i < m; ++i) {
		if (f[egg] < f[i]) {
			old = egg;
			egg = i;
		}
	}

	printf("iter \t egg \t f_val \t evals\n");
	printf("-------------------------------------------\n");
	for (i = 0; evals < iter; ++i) {
		egg = iterate(x, f, egg, old, m, n, func_num, i);
		if (egg != old) {
			p = 0;
			for (j = 0; j < m; ++j)
				p += f[j];

			printf("%d \t %d \t %.10lf \t %.10lf \t %d\n", i, egg, f[egg], p/m, evals);
		}

		old = egg;
	}

}