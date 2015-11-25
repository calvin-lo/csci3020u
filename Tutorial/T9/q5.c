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
    long double y;
    long double dx = 1 / (n + 1);
    long double x = 0;
    FILE *file = fopen("calculations.txt","w");
    #pragma omp parallel for private (x)
    for (int i = 0; i < n; i++)  {
            x = i * dx;
            y = exp(x) * cos(x) * sin(x) *sqrt(5 * x + 6.0);
            
            if (i % 1000000 == 0) {
                #pragma omp critical
                {
                    if (file != NULL) {
                        fprintf(file, "x: %le\ty: %le\n",x, y );  
                    }
                }

            }
    }
    fclose(file);
    return 0;
}
