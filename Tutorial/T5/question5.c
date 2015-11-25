
#include <stdio.h>
#include <pthread.h>

#define MAX_LEN 256
#define NUM_STUDENT 5

double total_grade = 0;
double total_bellcurve = 0;
double grades_list[NUM_STUDENT] = {0};
pthread_mutex_t mutex;
//pthread_barrier_t barrier; unknown type name ‘pthread_barrier_t’?


void *save_bellcurve(void *arg)
{
    double *local_grade = (double*) arg;
    pthread_mutex_lock(&mutex);
    total_grade += *local_grade ;
    pthread_mutex_unlock(&mutex);

    double bellcurve_grade = *local_grade * 1.50;
    pthread_mutex_lock(&mutex);
    total_bellcurve += bellcurve_grade;
    pthread_mutex_unlock(&mutex);

    FILE *f;
    f = fopen("bellcurve.txt", "a");
    fprintf(f,"%lf\n", bellcurve_grade);
    fclose(f);

    return NULL;
}

void read_grades()
{
    FILE *fp = fopen("grades.txt", "r");
    for (int i = 0; i < NUM_STUDENT; i++)
        fscanf(fp,"%lf",& grades_list[i]);
    fclose(fp);
    //pthread_barrier_wait(barrier);
}

int main()
{
    read_grades(); 
    //pthread_barrier_init(&barrier, NULL, NUM_STUDENT);

    pthread_t student[NUM_STUDENT];
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0 ; i <NUM_STUDENT ; i++)
    {
        pthread_create(&student[i], 0, save_bellcurve, &grades_list[i]);  
    }

    pthread_mutex_lock(&mutex);

    pthread_mutex_unlock(&mutex);
    
    for (int i = 0 ; i < NUM_STUDENT ; i++)
    {
        pthread_join(student[i], 0);
    }

    printf("Total Grade: %lf\n", total_grade);
    printf("Average before bellcurve: %lf\n", total_grade/NUM_STUDENT);
    printf("Average after bellcurve: %lf\n", total_bellcurve/NUM_STUDENT);

    pthread_mutex_destroy(&mutex);

    return 0;
}
