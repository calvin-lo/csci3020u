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

proc pop()  {
	proc *data = NULL;
	node_t * next_node = NULL;

	next_node = (head)->next;
	data = &(head)->process;
	free(head);
	head = next_node;

	return *data;
}

int delete_name(char *name)  {
	if (strcmp(head->process.name,name) == 0)  {
		node_t *temp = head;
		head = head->next;
		free(temp);
		return 1;
	}
	node_t *current = head->next;
	node_t *previous = head;
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
	node_t *current = head;
	node_t *previous = head;
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


	delete_name("emacs");
	delete_pid(12235);

	node_t * current = head;
    while (current != NULL) {
    	proc temp = pop();
        printf("%s\t" ,temp.name);
		printf("%d\t" ,temp.priority);
		printf("%d\t" ,temp.pid);
		printf("%d\n" ,temp.runtime);
        current = current->next;
    }
}