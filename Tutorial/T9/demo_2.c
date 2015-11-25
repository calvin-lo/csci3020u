#include <stdio.h>
#include <omp.h>
int main (int argc, char *argv[])
{
    int num = 0; // Watch out for race conditions!
    int thread_num, nthreads = 16;

    // ifdef means if the following is defined which means checking 
    // _OPENMP difined or not.
    #ifdef _OPENMP
    omp_set_num_threads(nthreads);
    #endif
    printf("Testing OpenMP, you should see each thread print...\n");
    
    // the OpemMp shared-memory parallel is defined by paragmas.
    // It defines a region of a parallel execution.
    #pragma omp parallel
    {
        // the OpemMp shared-memory parallel is defined by paragmas.
        // It will creat a critical section and it will only ececuted one thread
        // at a time.
        #pragma omp critical
        {
            
            // ifdef means if the following is defined which means checking 
            // _OPENMP difined or not.
            #ifdef _OPENMP
            num += 1; // THREAD SAFE INCREMENT
            thread_num = omp_get_thread_num();
            printf("This thread = %d, num = %d\n", thread_num, num);
            #endif
        }
    }
    return 0;
}
