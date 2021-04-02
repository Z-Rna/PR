#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 100000000; // 10**8
double step;

int main(int argc, char* argv[])
{

	const int threads = 8;
	omp_set_num_threads(threads);

	clock_t start, stop;
	double start_omp, stop_omp;
	double x, pi, sum = 0.0, tab[threads];
	int i;
	step = 1. / (double)num_steps;
	start_omp = omp_get_wtime();
#pragma omp parallel
	{
		int id = omp_get_thread_num();
		tab[id] = 0;

#pragma omp for nowait
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5) * step;

			tab[id] += 4.0 / (1. + x * x);
		}
#pragma omp atomic
		sum += tab[id];
	}

	pi = sum * step;
	stop_omp = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Rzeczywisty czas przetwarzania wynosi %f sekund\n", (stop_omp - start_omp));
	return 0;
}