#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int moving_sum[5] = {0,0,0,0,0};
sem_t sem;

typedef struct {
    int number;
    int index;
} num;

void *factorial(void *arg)
{
    num *n = (num*) arg;
    int sum = 1;
    int i = n->number;
    if (i != 0) {
        while (i > 1){
            sum *= i;
            i--;
        }
    }

    sem_wait(&sem);
    if (n->index > 0) {
        int pre = moving_sum[n->index - 1];
        sum += pre;
        moving_sum[n->index] += sum;
    }
    sem_post(&sem);

    return NULL;
}

int main(void) {

    printf("Enter five number: ");
    scanf("%d %d %d %d %d",&moving_sum[0], &moving_sum[1],
        &moving_sum[2], &moving_sum[3], &moving_sum[4]);


    sem_init(&sem, 0, 1);

    pthread_t pth1;
    pthread_t pth2;
    pthread_t pth3;
    pthread_t pth4;
    pthread_t pth5;

    sem_init(&sem, 0, 1);

    num n1;
    n1.number = moving_sum[0];
    n1.index = 0;
    num n2;
    n2.number = moving_sum[1];
    n2.index = 1;
    num n3;
    n3.number = moving_sum[2];
    n3.index = 2;
    num n4;
    n4.number = moving_sum[3];
    n4.index = 3;
    num n5;
    n5.number = moving_sum[4];
    n5.index = 4;

    pthread_create(&pth1, 0, factorial, &n1);
    pthread_create(&pth2, 0, factorial, &n2);
    pthread_create(&pth3, 0, factorial, &n3);
    pthread_create(&pth4, 0, factorial, &n4);
    pthread_create(&pth5, 0, factorial, &n5);


    pthread_join(pth1, 0);
    pthread_join(pth2, 0);
    pthread_join(pth3, 0);
    pthread_join(pth4, 0);
    pthread_join(pth5, 0);

    for (int i = 0; i < 5 ; i++)
        printf("%d ", moving_sum[i]);
    printf("\n");

    sem_destroy(&sem);
}