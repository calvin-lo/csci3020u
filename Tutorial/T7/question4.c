#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define SHELL "/bin/sh"

int main()  {
	pid_t pid;

	int status = 0;
	pid = fork();

	if (pid == 0)  {
		execl(SHELL, SHELL, "-c", "./process", NULL);
		return 0;
	}

	sleep(5);
	kill(pid + 1, SIGTSTP);

	sleep(10);
	kill(pid + 1,SIGCONT);

	waitpid(pid, &status, 0);
}