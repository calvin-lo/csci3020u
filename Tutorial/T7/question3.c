#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>

#define SHELL "/bin/sh"

int main()  {
	pid_t pid;

	pid = fork();

	if (pid == 0)  {
		execlp(SHELL, SHELL, "-c", "./process", NULL);
		return 0;
	}

	sleep(5);
	kill(pid + 1, SIGINT);
}