//question 2
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int ar[10];
	FILE *fp = fopen("question2.txt", "r");
	for (int i = 0; i < 10; i++)
		fscanf(fp, "%d", &ar[i]); 
	fclose(fp);
	for (int i = 0; i < 10; i++)
		printf("%d \n", ar[i]);
}