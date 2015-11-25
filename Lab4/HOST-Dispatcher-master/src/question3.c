#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)  {
	pid_t pid;

	pid = fork();

	if (pid == 0)  {
		exec();
	}

	sleep(5);
}