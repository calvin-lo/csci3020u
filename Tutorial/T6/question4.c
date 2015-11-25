#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdlib.h>

pthread_mutex_t mutex;

int buffer[5] = {0};
#define NUMBERS 10
sem_t empty;
sem_t full;


void *producer(void *arg)
{
    int in = 0;
    int* arr  = (int*) arg;
    for (int i = 0; i < NUMBERS; i++)  {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = arr[i];
        in = (in + 1) % 5;
        printf("Produced %d.\n", arr[i]);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        srand(time(NULL));
        sleep(rand()%5);
    }

    return NULL;
}
void *consumer()
{
    int out = 0;
    for (int i =NUMBERS; i > 0; i--)  {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int temp = buffer[out];
        buffer[out] = 0;
        out = (out + 1) % 5;
        printf("Consumed %d.\n", temp);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        srand(time(NULL));
        sleep(rand() % 5);

    }
    return NULL;
}

int main(void) {

    printf("Enter ten numbers: ");
    int arr[NUMBERS] = {0};
    scanf("%d %d %d %d %d %d %d %d %d %d",&arr[0], 
        &arr[1], &arr[2], &arr[3], &arr[4], 
        &arr[5], &arr[6], &arr[7], &arr[8], 
        &arr[9]);

    pthread_t producer_t;
    pthread_t consumer_t;

    sem_init(&empty, 0, 5);
    sem_init(&full, 0, 0);

    pthread_create(&producer_t, 0, producer, &arr);
    pthread_create(&consumer_t,0 , consumer, 0);


    pthread_join(producer_t, 0);
    pthread_join(consumer_t, 0);

    for (int i = 0; i < 5 ; i++)
        printf("%d ", buffer[i]);
    printf("\n");

    sem_destroy(&empty);
    sem_destroy(&full);


    //sem_destroy(&sem);
}