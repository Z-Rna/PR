#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 100000000; // 10**8
double step;

int main(int argc, char* argv[])
{
	omp_set_num_threads(2);

	clock_t start, stop;
	double start_omp, stop_omp;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start_omp = omp_get_wtime();
#pragma omp parallel
	{
#pragma omp for reduction(+:sum)
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5) * step;

			sum += 4.0 / (1. + x * x);
		}
	}

	pi = sum * step;
	stop_omp = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Rzeczywisty czas przetwarzania wynosi %f sekund\n", (stop_omp - start_omp));
	return 0;
}