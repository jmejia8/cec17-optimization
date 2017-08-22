#ifndef SUB_POPULATION
#define SUB_POPULATION 7
#endif

int evals = 0;

void myfunc(double *x, double *f, int nx, int mx, int func_num){
	// nx; dimesion
	// mx; pop_size
	++evals;
	cec17_test_func(x, f, nx, mx, func_num);
}

int is_in(int value, int* list, int list_size){
	int i;

	for (i = 0; i < list_size; ++i) {
		if (list[i] == value)
			return 1;
	}

	return 0;
}

void gen_subpopulation(int* items, int item_size, int pop_size){
	int i = 0, j;

	while (i < item_size){
		j = randint() % pop_size;
		if (!is_in(j, items, i))
			items[i++] = j;
	}
}

double masa (double x, double m, double M){
	// if (abs(M - m) < 1e-8)
	// 	return randm();

	// return  1 -  (x - m) / (M - m);

	return M - x;
}

void my_center(double* center,
				 double* population, 
					int* sub_population, 
				 double* fitness,
				 	int  pop_size, 
				 	int  subpop_size, 
				 	int  dimension)
{
	int i, j, k;
	double value, M, m, mass = 0, a;


	zeros(center, dimension);

	// M = 0; //;maximum(fitness, pop_size);
	// m =  minimum(fitness, pop_size);

	for (int i = 0; i < subpop_size; ++i) {
		if (M < fitness[sub_population[i]])
			M = fitness[sub_population[i]];
	}

	M *= 2;

	for (i = 0; i < subpop_size; ++i) {
		a = fitness[sub_population[i]];
		value = masa(a, m, M);

		mass += value;
		k     = dimension*sub_population[i];

		for (j = 0; j < dimension; ++j) {
			center[j] += value * population[k + j];
		}
	}

	for (int i = 0; i < dimension; ++i)
		center[i] /= mass;
		
}

void gen_child(double* child,
			   double* population,
			   double* center,
			      int* sub_population,
			      int  parent,
			      int pop_size,
			      int subpop_size,
			      int dimension, int gen)
{
	int i;
	double x, c, r, a ;

	int k = sub_population[ randint() % subpop_size ];
	k *= dimension;
	parent *= dimension;

	a = 0.01 + 2 * randm();


	for (i = 0; i < dimension; ++i) {
		x = population[parent + i];
		c = center[i];
		r = population[k + i];

		// important mutation
		child[i] = x + a * (c - r);

		while (fabs(child[i]) > 100){
			child[i] /= 2.0;
		}

	}


}

void show_best(double* population, double* fitness, int pop_size, int dimension){
	int i, mi = 0;
	for (int i = 1; i < pop_size; ++i) {
		if (fitness[i] < fitness[mi])
			mi = i;
	}

	double DTAP_ = diversity(population, pop_size, dimension);
	double DALL_ = DALL(population, pop_size, dimension);

	printf(">>>>  v = %.8lf \t  mean = %lg \t DTAP = %lf  \t DALL = %lf \n", fitness[mi],
																   mean(fitness, pop_size),
																   DTAP_, 
																   DALL_
																   );

	// mi *= dimension;
	// printf("==== soool === \n");
	// for (i = 0; i < dimension; ++i) {
	// 	printf("%lg, ", population[mi + i]);
	// }

	printf("\n=================================================\n");
}


void replace(double* population,
			 double* fitness,
			 int pop_size,
			 double* children,
			 double* fit_children,
			 int children_counter,
			 int dimension)
{
		int i, j, order[pop_size];
		order_desc(order, fitness, pop_size);
		for (i = 0; i < children_counter; ++i)
		{
			if (fit_children[i] < fitness[order[i]])
			{
				for (j = 0; j < dimension; ++j) {
					population[order[i]*dimension + j] = children[i*dimension + j];
				}

				fitness[order[i]] = fit_children[i];
			}
		}
}

// experimental
void replace2(double* population,
			 double* fitness,
			 int pop_size,
			 double* children,
			 double* fit_children,
			 int children_counter,
			 int dimension)
{
		int i, j, order[pop_size];
		order_desc(order, fitness, pop_size);
		for (i = 0; i < children_counter; ++i)
		{
			if (1 || fit_children[i] < fitness[order[i]])
			{
				for (j = 0; j < dimension; ++j) {
					population[order[i]*dimension + j] = children[i*dimension + j];
				}

				fitness[order[i]] = fit_children[i];
			}
		}
}

void optim(double* population, double* fitness, int pop_size,  int dimension, int func_num, int max_evals, int exec) {
	int i, j, l, k, t;
	int sub_population[SUB_POPULATION];

	// Children variables
	double center[dimension], child[dimension];
	double fitness_child[1];
	double* children     = allocSperms(dimension, pop_size);
	double* fit_children = allocSperms(1, pop_size);
	int children_counter = 0;


	double best = minimum(fitness, pop_size);
	double freal = 100*func_num;

	// calculate Error
	double myError = fabs(best - freal);

	// generation filename
	char fileName[256];
	FILE* myFile;

	for (t = 0; myError >= 1e-8 && evals < max_evals; ++t) {
		// show_best(population, fitness, pop_size, dimension);
	
		// for saving generation
		sprintf(fileName, "experiments/d%d/fun%d/run%d/generation%d.csv", dimension, func_num, exec, t);
		myFile = fopen(fileName, "wa");
		saveGeneration(myFile, population, fitness, pop_size, dimension);

		children_counter = 0;

		for (i = 0; i < pop_size; ++i) {
			gen_subpopulation(sub_population, SUB_POPULATION, pop_size);

			my_center(center,
					  population,
					  sub_population,
					  fitness,
					  pop_size,
					  SUB_POPULATION,
					  dimension);


			gen_child(child,
					  population,
					  center,
					  sub_population,
					  i,
					  pop_size,
					  SUB_POPULATION,
					  dimension, t);


			myfunc(child, fitness_child, dimension, 1, func_num);

			// save best childrens
			if (fitness_child[0] <= fitness[i]) {
				for (int j = 0; j < dimension; ++j)
					children[children_counter*dimension + j] = child[j];

				fit_children[children_counter] = fitness_child[0];
				++children_counter;
			}

		}

		// Replace
		replace(population,
				fitness,
			 	pop_size,
				children,
				fit_children,
			 	children_counter,
			 	dimension);

		best = minimum(fitness, pop_size);
		myError = fabs(best - freal);

		fclose(myFile);


	}

	// show_best(population, fitness, pop_size, dimension);


}