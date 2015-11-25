#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <stdbool.h>

#define BUFFER 256;
#define SHELL "/bin/sh"

typedef struct {
	char name[256];
	int priority;
	int pid;
	int runtime;
} proc;

typedef struct node {
	proc process;
	struct node* next;
} node_t;
 
node_t* queue =  NULL;

void push (proc process){
	node_t *new_node;
	new_node = malloc(sizeof(node_t));

	new_node->process = process;
	new_node->next = queue;
	queue = new_node;
}	

proc pop()  {
	proc *data = NULL;
	node_t * next_node = NULL;

	next_node = (queue)->next;
	data = &(queue)->process;
	free(queue);
	queue = next_node;

	return *data;
}

int delete_name(char *name)  {
	if (strcmp(queue->process.name,name) == 0)  {
		node_t *temp = queue;
		queue = queue->next;
		free(temp);
		return 1;
	}

	node_t *current = queue->next;
	node_t *previous = queue;
	while (current != NULL && previous != NULL) {
		if (strcmp((current->process.name),name) == 0)  {
			node_t *temp = current;
			previous->next = current->next;
			free(temp);
			return 1;
		} 
		previous = current;
		current = current->next;
	}

	return 0;

}

int delete_pid(int pid)  {
	node_t *current = queue;
	node_t *previous = queue;
	while (current != NULL && previous != NULL) {
		if (current->process.pid == pid)  {
			node_t *temp = current;
			previous->next = current->next;
			free(temp);
			return 1;
		} 
		previous = current;
		current = current->next;
	}

	return 0;
}

int main (void)  {

	FILE *f = fopen("processes_q5.txt", "r");
	char line[256];
	while (fgets(line, sizeof line, f) != NULL)  {
		proc data;
		char *parse;
		int i = 0;
		char temp_priority[256], temp_runtime[256];
		parse = strtok(line, ", ");
		while (parse != NULL)  {
			if (i == 0)
				strcpy(data.name, parse);
			if (i == 1)
				strcpy(temp_priority, parse);
			if (i == 2)
				strcpy(temp_runtime, parse);
			i++;
			parse = strtok(NULL, ", ");
		}
		data.priority = atoi(temp_priority);
		data.pid = 0;
		data.runtime = atoi(temp_runtime);
		push(data);

	}


	node_t * current = queue;
    while (current != NULL) {
    	if (current->process.priority == 0)  {
    		proc p = current->process;
    		printf("%s\n", p.name);
    		delete_name(p.name);
    		pid_t pid;
    		int status = 0;
    		pid = fork();
    		if (pid == 0)  {
    			execl(SHELL, SHELL, "-c", p.name, NULL);
    			p.pid = pid;
				return status;
    		}
    		sleep(p.runtime);
    		kill(pid, SIGINT);
    		waitpid(pid, &status, 0);
    		printf("%s\t" ,p.name);
			printf("%d\t" ,p.priority);
			printf("%d\t" ,p.pid);
			printf("%d\n" ,p.runtime);
    	}
    	current = current->next;
    }


    node_t *current2 = queue;
    while (current2 != NULL)  {
    	proc p = pop();
		pid_t pid;
    	int status = 0;
		pid = fork();
		if (pid == 0)  {
			execl(SHELL, SHELL, "-c", p.name, NULL);
			p.pid = pid;
			return status;
		}
		sleep(p.runtime);
		kill(pid, SIGINT);
		waitpid(pid, &status, 0);
		printf("%s\t" ,p.name);
		printf("%d\t" ,p.priority);
		printf("%d\t" ,p.pid);
		printf("%d\n" ,p.runtime);
		current2 = current2->next;
    }
}