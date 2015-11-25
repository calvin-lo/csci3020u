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
 
node_t* head =  NULL;

void push (proc process){
	node_t *new_node;
	new_node = malloc(sizeof(node_t));

	new_node->process = process;
	new_node->next = head;
	head = new_node;
}	

int main (void)  {

	FILE *f = fopen("processes.txt", "r");
	char line[256];
	while (fgets(line, sizeof line, f) != NULL)  {
		proc data;
		char *parse;
		int i = 0;
		char temp_priority[256], temp_pid[256], temp_runtime[256];
		parse = strtok(line, ", ");
		while (parse != NULL)  {
			if (i == 0)
				strcpy(data.name, parse);
			if (i == 1)
				strcpy(temp_priority, parse);
			if (i == 2)
				strcpy(temp_pid, parse);
			if (i == 3)
				strcpy(temp_runtime, parse);
			i++;
			parse = strtok(NULL, ", ");
		}
		data.priority = atoi(temp_priority);
		data.pid = atoi(temp_pid);
		data.runtime = atoi(temp_runtime);
		push(data);

	}

	node_t * current = head;
    while (current != NULL) {
        printf("%s\t" ,current->process.name);
		printf("%d\t" ,current->process.priority);
		printf("%d\t" ,current->process.pid);
		printf("%d\n" ,current->process.runtime);
        current = current->next;
    }
}