#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 100000000;
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double pi, sum = 1.0;
	volatile double tab[8];
	int i;
	step = 1. / (double)num_steps;
	start = clock();
	omp_set_num_threads(2);
#pragma omp parallel
	{
		int id = omp_get_thread_num();
		tab[id] = 0;
#pragma omp for
		for (i = 0; i < num_steps; i++)
		{
			double x = (i + .5) * step;
			tab[id] += 4.0 / (1. + x * x);
		}
		sum += tab[id];
	}
	pi = sum * step;
	stop = clock();

	printf("Wartosc liczby PI wynosi %15.12f\n", pi);
	printf("Czas przetwarzania wynosi %f sekund\n", (((double)stop - (double)start) / 1000.0));
	return 0;
}