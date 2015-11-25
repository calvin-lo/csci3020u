
#include <stdio.h>
#include <pthread.h>

void *hello_world()
{
	printf("hello world\n");
	return NULL;
}

void *goodbye() 
{
	printf("goodbye\n");
	return NULL;
}

int main()
{
    pthread_t pth;
    pthread_t pth2;

    pthread_create(&pth, 0, hello_world, NULL);
    pthread_create(&pth2, 0, goodbye, NULL);

    pthread_join(pth, 0);
    pthread_join(pth2, 0);

    return 0;
}
