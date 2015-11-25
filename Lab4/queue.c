/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Define your FIFO queue functions here, these will most likely be the
// push and pop functions that you declared in your header file

void push(node_t *tail, proc process)
{
	if (tail == NULL) {
		tail->process = process;
		return;
	}
	
	node_t *new_node;
	new_node = malloc(sizeof(node_t));

	new_node->process = process;
	new_node->next = tail;
	tail = new_node;
}

proc pop(node_t *tail)
{
	proc data;
	node_t * next_node = NULL;

	next_node = tail->next;
	data = tail->process;
	free(tail);
	tail = next_node;

	return data;
}
