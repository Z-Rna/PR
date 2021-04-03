#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 100000000; //sto milionow
double step;

int main(int argc, char* argv[])
{
	double start, stop;
	double pi, sum = 0.0;
	volatile double tab[50];
	int i;
	step = 1. / (double)num_steps;
	omp_set_num_threads(2);
	for (int j = 0; j < 30; j++)
	{
		start = omp_get_wtime();
		sum = 0;

#pragma omp parallel 
		{
			int id = omp_get_thread_num();
			tab[j + id] = 0;
#pragma omp for nowait
			for (i = 0; i < num_steps; i++)
			{
				double x = (i + .5) * step;
				tab[j + id] += 4.0 / (1. + x * x);
			}
#pragma omp atomic 
			sum += tab[id + j];
		}
		pi = sum * step;

		stop = omp_get_wtime();

		printf("Czas rzeczywisty iter %d wynosi %f sekund\n", j, (stop - start));
	}
	return 0;
}