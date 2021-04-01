#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 100000000; // 10**8
double step;

int main(int argc, char* argv[])
{

	int threads = 8;
	omp_set_num_threads(threads);

	clock_t start, stop;
	double start_omp, stop_omp;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	//start = clock();
	start_omp = omp_get_wtime();
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
	//stop = clock();
	stop_omp = omp_get_wtime();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	//printf("Czas przetwarzania wynosi %f sekund\n", \
		((double)(stop - start) / 1000.0));
	printf("Rzeczywisty czas przetwarzania wynosi %f sekund\n", \
		((double)(stop_omp - start_omp) ));
	return 0;
}