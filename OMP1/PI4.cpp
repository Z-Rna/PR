#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 100000000; // 10**8
double step;

int main(int argc, char* argv[])
{
	omp_set_num_threads(2);
	double start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = omp_get_wtime();
#pragma omp parallel
	{
		double sum1 = 0;
#pragma omp for
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5) * step;

			sum1 += 4.0 / (1. + x * x);
		}
#pragma omp atomic
		sum += sum1;
	}

	pi = sum * step;
	stop = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Rzeczywisty czas przetwarzania wynosi %f sekund\n", (stop - start));
	return 0;
}