
#include <stdio.h>
#include <pthread.h>

#define MAX_LEN 256
#define NUM_STUDENT 10

int total_grade = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *class_total(void *arg)
{
    int *local_grade = (int*) arg;
    pthread_mutex_lock(&mutex);
    total_grade += *local_grade ;
    printf("Thread: %d\n", *local_grade);
    pthread_mutex_unlock(&mutex);


    
    return NULL;
}


int main()
{
    int grades_list[NUM_STUDENT] = {0};
    for (int i = 0; i < NUM_STUDENT  ; i++)
    {
        printf("Enter student %d's grade: ", i+1 );
        scanf("%d", &grades_list[i]);
    }

    pthread_t student[NUM_STUDENT];

    for (int i = 0 ; i <NUM_STUDENT ; i++)
    {
        pthread_create(&student[i], 0, class_total, &grades_list[i]);  
    }

    for (int i = 0 ; i < NUM_STUDENT ; i++)
    {
        pthread_join(student[i], 0);
    }

    printf("Class Total: %d\n", total_grade);

    return 0;
}
