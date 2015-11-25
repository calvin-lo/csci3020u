
#include <stdio.h>
#include <pthread.h>

#define MAX_LEN 256
#define NUM_STUDENT 5

typedef struct 
{
    char name[MAX_LEN];
    int student_id;
    double grade;

}student;

void *bellcurve(void *arg)
{
    student *local_student = (student*) arg;
    local_student->grade *= 1.50;
    printf("%s  %d  %lf\n", local_student->name, local_student->student_id, local_student->grade);

    return NULL;
}


int main()
{
    student student_list[NUM_STUDENT] = {};
    for (int i = 0; i < NUM_STUDENT  ; i++)
    {
        printf("Enter student %d's name, id, grade: ", i+1 );
        scanf("%s %d %lf", student_list[i].name,&student_list[i].student_id, &student_list[i].grade);
    }

    pthread_t student[NUM_STUDENT];

    for (int i = 0 ; i <NUM_STUDENT ; i++)
    {
        pthread_create(&student[i], 0, bellcurve, &student_list[i]);  
    }

    for (int i = 0 ; i < NUM_STUDENT ; i++)
    {
        pthread_join(student[i], 0);
    }


    return 0;
}
