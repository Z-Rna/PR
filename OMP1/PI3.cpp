#include <stdio.h>
#include <time.h>
#include "omp.h"

long long num_steps = 100000000; // 10**8
double step;

int main(int argc, char* argv[])
{

	omp_set_num_threads(8);
	clock_t start, stop;
	double x, pi, sum = 0.0;
	int i;
	step = 1. / (double)num_steps;
	start = clock();
#pragma omp parallel for
	for (i = 0; i < num_steps; i++)
	{
		double x = (i + .5) * step;
#pragma omp atomic
		sum += 4.0 / (1. + x * x);
	}

	pi = sum * step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Rzeczywisty czas przetwarzania wynosi %f sekund\n", (((double)stop - (double)start) / 1000.0));
	return 0;
}