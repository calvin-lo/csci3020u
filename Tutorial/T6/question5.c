#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

int total_sum = 0;
sem_t sem;

void *factorial(void *arg)
{
    int *n = (int*) arg;
    int sum = 1;
    int i = *n;
    if (i != 0) {
        while (i > 1){
            sum *= i;
            i--;
        }
    }

    sem_wait(&sem);

    total_sum += sum;

    sem_post(&sem);
    
    return NULL;
}

int main(void) {
    pid_t PID = 0;

    printf("Enter five numbers: ");
    int arr[5] = {0};
    scanf("%d %d %d %d %d",&arr[0], 
        &arr[1], &arr[2], &arr[3], &arr[4]);
    FILE *fp = fopen("numbers.txt","w");
    fprintf(fp, "%d %d %d %d %d",arr[0], 
        arr[1], arr[2], arr[3], arr[4] );
    fclose(fp);
   PID = fork();
    if (PID == -1) {
        return 0;
    }
    if (PID == 0) {
        //Child process:
        FILE *in = fopen("numbers.txt","r");
        int num[5] = {0};
        for (int n = 0; n < 5; n++) {
            fscanf(in, "%d", &num[n]);
        }

        pthread_t pth1;
        pthread_t pth2;
        pthread_t pth3;
        pthread_t pth4;
        pthread_t pth5;

        sem_init(&sem, 0, 1);
        pthread_create(&pth1, 0, factorial, &num[0]);
        pthread_create(&pth2, 0, factorial, &num[1]);
        pthread_create(&pth3, 0, factorial, &num[2]);
        pthread_create(&pth4, 0, factorial, &num[3]);
        pthread_create(&pth5, 0, factorial, &num[4]);


        pthread_join(pth1, 0);
        pthread_join(pth2, 0);
        pthread_join(pth3, 0);
        pthread_join(pth4, 0);
        pthread_join(pth5, 0);

        sem_destroy(&sem);

        FILE *out = fopen("sum.txt", "w");
        fprintf(out, "%d\n", total_sum);

        fclose(in);
        fclose(out);

        return 0;
    } 
    else {
        wait(&PID);
        FILE *rf = fopen("sum.txt","r");
        int tsum = 0;
        fscanf(rf, "%d", &tsum);
        printf("Total sum: %d.\n", tsum);

        fclose(rf);
    }
}