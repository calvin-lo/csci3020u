/*
 * MyShell Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include "utility.h"
#include "myshell.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256

// Put global environment variables here
 extern char **environ;
// Define functions declared in myshell.h here

int main()
{
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };
    char command[BUFFER_LEN] = { 0 };
    char arg[BUFFER_LEN] = { 0 };
    char input[BUFFER_LEN] = {0}

    // Parse the commands provided using argc and argv

    if (argc == 1)  {
        strcpy(input, argv[1]);
    }
    /*if (argc == 3){
        strcpy(command, argv[1]);
        strcpy(arg, argv[2]);
    }*/
    File *fp = fopen(input,"r");
    
    char cwd[BUFFER_LEN];
    printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
    // Perform an infinite loop getting command input from users
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
        // Perform string tokenization to get the command and argument
        int pos = 0;
        char *parse;
        parse = strtok(buffer , " ");
        strcpy(command, parse); 
        while (parse!= NULL)  {
            if (pos == 1)
            {
                strcpy(arg, parse);
                strcat(arg, " ");
            }
            if (pos > 1)
            {
                strcat(arg, parse);
                strcat(arg, " ");
            }
            pos++;
            parse = strtok (NULL, " ");

        }
        strtok(command, "\n"); //clear the newline of the command
        strtok(arg, "\n");;
        // Check the command and execute the operations for each command
        // cd command -- change the current directory
        if (strcmp(command , "cd") == 0)
        {
            chdir(arg);
            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // other commands here...
        // clc
        else if (strcmp(command, "clc") == 0)
        {
            system("clear");
            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // dir
        else if (strcmp(command,"dir") == 0)
        {
            DIR *dp;
            struct dirent *dir = NULL;
            dp = opendir(arg);
            if (dp)
            {
                while ((dir = readdir(dp)) != NULL)
                    printf("%s\n", dir->d_name);
                closedir (dp);
            }
            else
                perror ("");

            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // environ
        else if (strcmp(command,"environ") == 0)
        {
            int i = 0;
            while (environ[i])
                printf("%s\n", environ[i++]);

            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // echo
        else if (strcmp(command,"echo") == 0)
        {
            printf("%s\n", arg);
            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // help
        else if (strcmp(command, "help") == 0)
        {

            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // pause
        else if (strcmp(command,"pause") == 0)
        {
            fgets(buffer,BUFFER_LEN,stdin); 

            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
        // quit command -- exit the shell
        else if (strcmp(command, "quit") == 0)
        {
            return EXIT_SUCCESS;
        }

        // Unsupported command
        else
        {
            fputs("Unsupported command, use help to display the manual\n", stderr);
            printf("> %s$ ", getcwd(cwd, sizeof(cwd)));
        }
    }
    return EXIT_SUCCESS;
}
