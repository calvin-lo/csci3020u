#include <stdlib.h>
#include <stdio.h>

int main (void)
{
double ar[5] = {1.2,5.5,2.1,3.3,3.3};
for (int i = 1; i< 5 ; i++){
	if (ar[i] > ar[i-1])
		printf("%f greater than %f \n", ar[i], ar[i-1]); 
	else if (ar[i] < ar[i-1])
		printf("%f less than %f \n", ar[i], ar[i-1]);
	else
		printf("%f is the same as %f \n", ar[i], ar[i-1]);
}
}