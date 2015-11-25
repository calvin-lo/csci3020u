#include <stdio.h>
#include <string.h>

#define NRM  "\x1B[0m"
#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define YEL  "\x1B[33m"
#define BLU  "\x1B[34m"
#define MAG  "\x1B[35m"
#define CYN  "\x1B[36m"

int main()
{
    char color[7][8];
   	strcpy(color[0], NRM); strcpy(color[1], RED);  strcpy(color[2], GRN);  strcpy(color[3], YEL);
   	strcpy(color[4], BLUE);  strcpy(color[5], MAG);  strcpy(color[6], CYN); 
   /* char nrm[8] ; strcpy(nrm, NRM);
    char grn[8];  strcpy(red, GRN);
    char yel[8] ; strcpy(nrm, YEL);
    char blu[8];  strcpy(red, BLU);
    char nrm[8] ; strcpy(nrm, MAG);
   	char red[8];  strcpy(red, CYN);*/

    printf("%sred\n", color[0]);
    printf("%sgreen\n", GRN);
    printf("%syellow\n", YEL);
    printf("%sblue\n", BLU);
    printf("%smagenta\n", MAG);
    printf("%scyan\n", CYN);
    printf("%snormal\n", NRM);



    return 0;
}