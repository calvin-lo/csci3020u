
#include <stdio.h>
#include <pthread.h>
#include <math.h>


void *bellcurve(void *arg)
{
    double *local_grade = (double*) arg;
    double bellcurve_grade = *local_grade * 1.5;
    printf("%lf\n", bellcurve_grade);

    return NULL;
}


int main()
{
    double grade[5] = { 0 };
    for (int i = 0; i < 5 ; i++)
    {
        printf("Enter student %d's grade: ", i+1 );
        scanf("%lf", &grade[i]);
    }

    pthread_t student1;
    pthread_t student2;
    pthread_t student3;
    pthread_t student4;
    pthread_t student5;


    pthread_create(&student1, 0, bellcurve, &grade[0]);
    pthread_create(&student2, 0, bellcurve, &grade[1]);
    pthread_create(&student3, 0, bellcurve, &grade[2]);
    pthread_create(&student4, 0, bellcurve, &grade[3]);
    pthread_create(&student5, 0, bellcurve, &grade[4]);

    pthread_join(student1, 0);
    pthread_join(student2, 0);
    pthread_join(student3, 0);
    pthread_join(student4, 0);
    pthread_join(student5, 0);

    return 0;
}
