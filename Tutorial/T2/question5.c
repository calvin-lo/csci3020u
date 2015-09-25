#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

double euclid_dist(int x1,int y1,int x2,int y2) {
	double x = x1 - x2;
	double y = y1 - y2;
	double dist; 
	dist = pow(x,2) + pow(y,2);
	dist = sqrt(dist);

	return dist;
	
}

int main (void)
{
	int x[1][2];
	int y[1][2];
	srand(time(NULL));
	for (int i = 0; i< 10 ; i++){ 
		x[0][0] = rand()%100 + 1;
		y[0][0] = rand()%100 + 1;
		x[0][1] = rand()%100 + 1;
		y[0][1] = rand()%100 + 1;
		double dist = euclid_dist(x[0][0],y[0][0],x[0][1],y[0][1]);
		printf("x1:%d	y1:%d	x2:%d	y2:%d	Euclidean distance: %f \n", x[0][0],y[0][0],x[0][1],y[0][1],dist);
	}
}
