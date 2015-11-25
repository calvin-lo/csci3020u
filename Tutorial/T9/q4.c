#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define size 100

int main ()
{
   


    int a[size][size];
    int b[size][size];
    int r[size][size];
    int i,j,n;


    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            a[i][j] = i + j;
        }
    }
    for (int i = size; i > 0; i--) {
        for (int j = size; j > 0; j--) {
            b[i][j] = i + j;
        }
    }

    int thread_num, nthreads = 10;
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif

    #pragma omp parallel for private(i,j,n)
    for (i = 0; i < size; i++) {
        thread_num = omp_get_thread_num();
        printf("This thread = %d, doing row %d\n", thread_num, i);
        for (j = 0; j < size; j++)
            for (n = 0; n < size; n++)
                r[i][j] = a[i][n] * b[n][j];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0 ; j < size; j++) {
            printf("%d\t", r[i][j]);
        }
        printf("\n");
    }
}
