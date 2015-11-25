/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"
#include <string.h>
#include <ctype.h>

// Define your utility functions here, you will likely need to add more...

// int alloc_mem(resources res, int size)
// {
//      ...
// }

// free_mem(resources res, int index, int size)
// {
//      ...
// }

void load_dispatch(char *dispatch_file, node_t *queue)
{
	FILE * file = fopen(dispatch_file, "r");
	while (!feof(file))  {
    	int size = 8;
    	int *info = malloc(sizeof(int) * size);
    	int i = 0;
    	while(!feof(file) && i < size)  {
    		char number[] = "\0\0\0\0";
    		char d = '\0';
    		int n = 0;
    		while (!feof(file) && isdigit(d = fgetc(file)))  {
    			number[n++] = d;
    		}
    		if (strlen(number) > 0)  {
    			info[i++] = atoi(number);
    		}
    		if(d == '\n')  {
    			break;
    		}
    	}

    	if (i < size)  {
    		free(info);
    		info = NULL;
    	}

    	proc process;
    	process.pid = 0;
    	process.arrival_time = info[0];
    	process.priority = info[1];
    	process.processor_time = info[2];
    	process.MBytes = info[3];
    	process.rs.num_printers = info[4];
    	process.rs.num_scanners = info[5];
    	process.rs.num_modems = info[6];
    	process.rs.num_CDs = info[7];

    	push(&queue, process);
    	
   	}
}

