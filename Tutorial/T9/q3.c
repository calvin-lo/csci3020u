#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int main ()
{
    int x[100000000];
    for (int i = 0; i < 100000000 ; i++)  {
        x[i] = rand() % 100 + 1;
    }

    int norm = 0;
    int st = 0;
    int et = 0;
    int nthreads = 5;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    st = omp_get_wtime();
    for (int i = 0; i < 100000000 ; i++)  {
        norm += fabs(x[i]);
    }
    et = omp_get_wtime();

    printf("Time for serial: %d\n", et - st);

    norm = 0;
    st = omp_get_wtime();

    #pragma omp parallel for reduction(+: norm)
    for (int i = 0; i < 100000000 ; i++)  {
            norm += fabs(x[i]);
        }

    et = omp_get_wtime();
    printf("Time for parallel: %d\n", et - st);
    return 0;
}

// The parallel for loop with a reduction using OpenMP is faster than
// serial for loop.
