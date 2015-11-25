#define _XOPEN_SOURCE 700
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

/**
 * A simple forking example. Forks and both child and
 * parent print out different messages.
 */
int main(void) {
	pid_t PID = 0;

	PID = fork();
	int status = 0;
	
	if (PID == -1) {
        return 0;
    }

    //Is it a child process or the parent?
    if (PID == 0) {
        //Child process:
        sleep(1);
        printf("Child process\n");

        //Finish on success
        status = 0;
        return status;
    } else {
        //Parent process:
        wait(&PID);
        if (status == 0)
        	printf("Parent process\n");
    }
}