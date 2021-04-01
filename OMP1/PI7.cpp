#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 100000000; //sto milionow
double step;

int main(int argc, char* argv[])
{
	clock_t start, stop;
	double start_omp, stop_omp;
	double x, pi, sum = 0.0;
	volatile double tab[50];
	int i;
	step = 1. / (double)num_steps;
	omp_set_num_threads(2);
	for (int j = 0; j < 30; j++)
	{

		start = clock();
		start_omp = omp_get_wtime();
		sum = 0;

#pragma omp parallel 
		{//double sum1 = 0;
			int id = omp_get_thread_num();
			tab[j + id] = 0;
#pragma omp for nowait
			for (i = 0; i < num_steps; i++)
			{
				double x = (i + .5) * step;
				//#pragma omp flush(sum)
				//#pragma omp atomic 
				tab[j + id] += 4.0 / (1. + x * x);
			}
#pragma omp atomic 
			sum += tab[id + j];
		}
		pi = sum * step;

		stop = clock();
		stop_omp = omp_get_wtime();

		//printf("Wartosc liczby PI wynosi %15.12f\n", pi);
		//printf("Czas przetwarzania wynosi %f sekund\n", ((double)(stop - start) / 1000.0));
		printf("Czas rzeczywisty iter %d wynosi %f sekund\n", j, ((double)(stop_omp - start_omp)));
	}
	return 0;
}