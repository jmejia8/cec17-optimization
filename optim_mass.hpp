#ifndef SUB_POPULATION
#define SUB_POPULATION 7
#endif

int evals = 0;

void myfunc(double *x, double *f, int nx, int mx, int func_num){
	// nx; dimesion
	// mx; pop_size
	evals++;
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

void my_center(double* center,
				 double* population, 
					int* sub_population, 
				 double* fitness,
				 	int  pop_size, 
				 	int  subpop_size, 
				 	int  dimension)
{
	int i, j, k;
	double value, M, mass = 0;


	zeros(center, dimension);

	M = 2 * maximum(fitness, pop_size);

	for (i = 0; i < subpop_size; ++i) {
		
		value = M - fitness[sub_population[i]];
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
			      int dimension)
{
	int i;
	double x, c, r, a ;

	int k = sub_population[ randint() % subpop_size ];
	k *= dimension;
	parent *= dimension;

	a = 2 * randm();

	for (i = 0; i < dimension; ++i) {
		x = population[parent + i];
		c = center[i];
		r = population[k + i];

		// important mutation
		child[i] = x + a * (c - r);
	}

}

void show_best(double* population, double* fitness, int pop_size, int dimension){
	int i, mi = 0;
	for (int i = 1; i < pop_size; ++i) {
		if (fitness[i] < fitness[mi])
			mi = i;
	}

	printf(">>>>  v = %lg \t  mean = %lg \n", fitness[mi], mean(fitness, pop_size));

	mi *= dimension;
	for (i = 0; i < dimension; ++i) {
		printf("%lg \t", population[mi + i]);
	}

	printf("\n=================================================\n");
}

void optim(double* population, double* fitness, int pop_size,  int dimension, int func_num, int max_iter) {
	int i, j, l, k, t;
	int sub_population[SUB_POPULATION];
	double center[dimension], child[dimension];
	double fitness_child[1];

	double* children     = allocSperms(dimension, pop_size);
	double* fit_children = allocSperms(1, pop_size);
	int children_counter = 0;

	// experimental
	int saves[pop_size];

	for (t = 0; t < max_iter && evals < 300000; ++t) {
		printf("\niter = %d \n", t);
		printf("evals  = %d\n", evals);
		show_best(population, fitness, pop_size, dimension);

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
					  dimension);

			// if (t == 100)
			// {
				
			// 	for (int j = 0; j < SUB_POPULATION; ++j)
			// 	{
			// 		printf("%d, ", sub_population[j]);
			// 	}

			// 	exit(0);
			// }

			myfunc(child, fitness_child, dimension, 1, func_num);

			// save best childrens
			if (fitness_child[0] <= fitness[i]) {
				for (int j = 0; j < dimension; ++j)
					children[children_counter*dimension + j] = child[j];

				fit_children[children_counter] = fitness_child[0];
				saves[children_counter] = i;
				++children_counter;
			}

		}

		// printf("\n===================>  mios = %d\n", children_counter);
		// Replace
		int order[pop_size];
		order_desc(order, fitness, pop_size);
		for (int i = 0; i < children_counter; ++i)
		{
			if (fit_children[i] < fitness[order[i]])
			{
				for (int j = 0; j < dimension; ++j) {
					population[order[i]*dimension + j] = children[i*dimension + j];
				}

				fitness[order[i]] = fit_children[i];
			}
		}


	}


}
