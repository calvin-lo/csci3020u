/*
 * Host Dispatcher Shell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "utility.h"
#include "hostd.h"

// Put macros or constants here using #define
#define MEMORY 1024

// Put global environment variables here
node_t *dispatch_list;


// Define functions declared in hostd.h here
void print_process(proc process) {
    printf("<pid>\t<priority>\t<processor time>\t<Memory Location>\t<MBytes>\n");
    printf("%d\t%d\t%d\t%d\t%d\n",process.pid, process.priority, process.processor_time, process.memory_index, process.MBytes);
    printf("<#printers>\t<#scanners>\t<#modems>\t<#CDs>\n");
    printf("%d\t%d\t%d\t%d\n", process.rs.num_printers, process.rs.num_scanners, process.rs.num_modems, process.rs.num_CDs);

}

int main(int argc, char *argv[])
{
    // ==================== YOUR CODE HERE ==================== //
    
    // Load the dispatchlist
    char * dispatch_file = NULL;

    if(argc > 1)
        dispatch_file = argv[1];

    load_dispatch(dispatch_file, dispatch_list);
    
    // Add each process structure instance to the job dispatch list queue

    // Iterate through each item in the job dispatch list, add each process
    // to the appropriate queues

    // Allocate the resources for each process before it's executed

    // Execute the process binary using fork and exec

    // Perform the appropriate signal handling / resource allocation and de-alloaction

    // Repeat until all processes have been executed, all queues are empty
     
    return EXIT_SUCCESS;
}
