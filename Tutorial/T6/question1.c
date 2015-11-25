#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>


int main() {
 
    pid_t PID_A = 0;
    pid_t PID_B = 0;

    PID_A = fork();

    if (PID_A == -1) {
        return 0;
    }

    if (PID_A == 0) {
        FILE *fp1;
        fp1 = fopen("child_1.txt","w");
        fprintf(fp1,"child_1");
        fclose(fp1);

        return 0;
    } else {
        sleep(1);
        char s1[256] = {0};
        FILE *fr1;
        fr1 = fopen("child_1.txt","r");
        fscanf(fr1,"%s", s1);
        printf("%s\n", s1);
        fclose(fr1);
    }

    PID_B = fork();
    if (PID_B == -1)  {
        return 0;
    }
    if (PID_B == 0) {
        FILE *fp2;
        fp2 = fopen("child_2.txt","w");
        fprintf(fp2,"child_2");
        fclose(fp2);

        return 0;
    } else {
        sleep(1);
        char s2[256] = {0};
        FILE *fr2;
        fr2 = fopen("child_2.txt","r");
        fscanf(fr2,"%s", s2);
        printf("%s\n",s2);
        fclose(fr2);
    }
    return 0;
}