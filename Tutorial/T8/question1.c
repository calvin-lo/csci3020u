#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct {
	char parent[256];
	char name[256];
	int priority;
	int memory;
} proc;

typedef struct node{
	proc process;
	struct node *left;
	struct node *right;
} node_t;


void dFS (node_t *tree)  {
	if (tree->left != NULL)
		dFS(tree->left);
	if (tree->right != NULL)
		dFS(tree->right);
}
void add_node(node_t *tree, node_t * child)  {
	if (tree->left == NULL)  {
		tree->left = child;
	} else if (tree->right == NULL)  {
		tree->right = child;
	} else {
		printf("Error...");
	}
}

void print_tree(node_t * current) {

	if (current != NULL && (current->left != NULL || current -> right != NULL))
		printf("\nParent: %s %d %d", current->process.name, current->process.priority, current->process.memory);
	if (current->left != NULL)
		printf(" Left Child: %s %d %d", current->left->process.name, current->left->process.priority, current->left->process.memory);
	if (current->right != NULL)
		printf(" Right Child: %s %d %d", current->right->process.name, current->right->process.priority, current->left->process.memory);
	if (current->left != NULL)
		print_tree(current->left);
	if (current->right != NULL)
		print_tree(current->right);
}

int search_parent (node_t *tree_list, proc process, int total_record)  {
	for (int i = 0; i < total_record; i++ ) {
		if (strcmp(tree_list[i].process.name, process.parent) == 0)  {
			return i;
		}
	}
	return -1;
}


int main(void)  {

	FILE *f = fopen("processes_tree.txt", "r");
	char line[256];
	node_t *tree_list = (node_t*)malloc(sizeof(node_t));
	node_t *tree = (node_t*)malloc(sizeof(node_t));
	int total_record = 0;


	while (fgets(line, sizeof line, f) != NULL)  {
		proc process;
		char *parse;
		int i = 0;
		char temp_priority[256], temp_memory[256];
		parse = strtok(line, ", ");
		while (parse != NULL)  {
			if (i == 0)
				strcpy(process.parent, parse);
			if (i == 1)
				strcpy(process.name, parse);
			if (i == 2)
				strcpy(temp_priority, parse);
			if (i == 3)
				strcpy(temp_memory, parse);
			i++;
			parse = strtok(NULL, ", ");
		}
		process.priority = atoi(temp_priority);
		process.memory = atoi(temp_memory);
		node_t temp;
		temp.process = process;
		temp.left = NULL; temp.right = NULL;
		tree_list[total_record] = temp;
		total_record++;
	}
	for (int i = 0; i < total_record; i++) {
		if (strcmp(tree_list[i].process.parent, "NULL") == 0)  {
			tree = &tree_list[i];
		} else {
			int n = search_parent(tree_list, tree_list[i].process,total_record);
			if (n > -1)  {
				add_node(&tree_list[n],&tree_list[i]);
			}
		}
	}
	print_tree(tree);
	printf("\n");
}