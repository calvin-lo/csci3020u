#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main (int argc, char *argv[])
{

    int nthreads = 0;

    if (argc > 0)
        nthreads = *argv[0];

    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    int n = 100000000;
    long double y[n];
    long double dx = 1 / (n + 1);
    long double x = 0;

    #pragma omp parallel for private (x)
    for (int i = 0; i < n; i++)  {
            x = i * dx;
            y[i] = exp(x) * cos(x) * sin(x) *sqrt(5 * x + 6.0);
    }
    return 0;
}
