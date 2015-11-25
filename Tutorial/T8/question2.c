#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MEMORY 1024
#define BUFFER 256
#define SHELL "/bin/sh"

typedef struct {
	char name[BUFFER];
	int priority;
	int pid;
	int address;
	int memory;
	int runtime;
	bool suspended;
} proc;

typedef struct node {
	proc process;
	struct node* next;
} node_t;
node_t * priority = NULL;
node_t * secondary = NULL;

void push (proc process){
	if (process.priority == 0)  {
		node_t *new_node;
		new_node = malloc(sizeof(node_t));

		new_node->process = process;
		new_node->next = priority;
		priority = new_node;
	} else {
		node_t *new_node;
		new_node = malloc(sizeof(node_t));

		new_node->process = process;
		new_node->next = secondary;
		secondary = new_node;
	}
}	

proc pop(int type)  {
	proc data;
	node_t * next_node = NULL;

	// type 1 = priority
	if (type == 1)  {
		next_node = priority->next;
		data = priority->process;
		free(priority);
		priority = next_node;
	} else {
		next_node = secondary->next;
		data = secondary->process;
		free(secondary);
		secondary = next_node;
	}
	return data;

}


int main (void) {

	int avail_mem[MEMORY] = {0};
	FILE *f = fopen("processes_q5.txt", "r");
	char line[BUFFER];
	while (fgets(line, sizeof line, f) != NULL)  {
		proc data;
		char *parse;
		int i = 0;
		char temp_priority[BUFFER], temp_runtime[BUFFER], temp_memory[BUFFER];
		parse = strtok(line, ", ");
		while (parse != NULL)  {
			if (i == 0)
				strcpy(data.name, parse);
			if (i == 1)
				strcpy(temp_priority, parse);
			if (i == 2)
				strcpy(temp_memory, parse);
			if (i == 3)
				strcpy(temp_runtime, parse);
			i++;
			parse = strtok(NULL, ", ");
		}
		data.priority = atoi(temp_priority);
		data.memory = atoi(temp_memory);
		data.pid = 0;
		data.runtime = atoi(temp_runtime);
		
		push(data);

	}

	node_t * current = priority;
	while (current != NULL) {
		proc p = pop(1);
		int i;
		for (i = 0; i < p.memory; i++)  {
			avail_mem[i] = 1;
		}
		p.address = 0;
		printf("%s, %d, %d, %d, %d\n", p.name, p.priority, p.pid, p.memory, p.runtime);
		pid_t pid;
    	int status = 0;
		pid = fork();
		if (pid == 0)  {
			execl(SHELL, SHELL, "-c", p.name, NULL);
			return status;
		}
		sleep(p.runtime);
    	kill(pid, SIGINT);
    	waitpid(pid, &status, 0);
    	for (i = 0; i < MEMORY; i++)  {
			avail_mem[i] = 0;
		}
		current = current->next;
	}


	current = secondary;
	while (current != NULL) {
		proc p = pop(2);
		if (p.memory <= MEMORY)	{
			int i;
			for (i = 0; i < p.memory; i++)  {
				avail_mem[i] = 1;
			}
			p.address = 0;
			printf("%s, %d, %d, %d, %d\n", p.name, p.priority, p.pid, p.memory, p.runtime);
			pid_t pid;
	    	int status = 0;

			if (p.suspended == true && p.pid != 0)  {
				kill(p.pid, SIGCONT);
			}
			pid = fork();
			if (pid == 0)  {
				execl(SHELL, SHELL, "-c", p.name, NULL);
				return status;
			}
			p.pid = pid;
			sleep(1);
			kill(p.pid, SIGTSTP);
			p.runtime --;
			p.suspended = true;

			if (p.runtime > 0)
				push(p);
			else
	    		kill(p.pid,SIGINT);
	    	
	    	waitpid(pid, &status, 0);


	    	for (i = 0; i < MEMORY; i++)  {
				avail_mem[i] = 0;
			}
		} else {
			push(p);
		}

		current = secondary;
	}
}