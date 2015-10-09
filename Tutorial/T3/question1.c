//question 1
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	char fname[10];
	int age, height;
	printf("Enter your first name, age and height:");
	scanf("%s %d %d", fname, &age, &height);
	printf("First name: %s, Age: %d, Height: %d \n",fname, age, height);
}