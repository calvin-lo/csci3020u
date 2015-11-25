/*
 * Tutorial 4 Jeopardy Project for SOFE 3950U / CSCI 3020U: Operating Systems
 *
 * Copyright (C) 2015, <GROUP MEMBERS>
 * All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "questions.h"
#include "players.h"
#include "jeopardy.h"

// Put macros or constants here using #define
#define BUFFER_LEN 256
#define NUM_PLAYERS 4
#define NUM_QUESTIONS 12

// Put global environment variables here

// Processes the answer from the user containing what is or who is and tokenizes it to retrieve the answer.
void tokenize(char *input, char **tokens)
{
	char ans[BUFFER_LEN];
    int i = 0;    
    char *parse;
    char blah_one[BUFFER_LEN];
    char blah_two[BUFFER_LEN];
    parse = strtok(input , " ");
    while (parse != NULL)
    {
    	if (i == 0)
    		strcpy(blah_one,parse);
    	if (i == 1)
    		strcpy(blah_two,parse);
    	if (i == 2)  
    		strcpy(ans,parse);
    	i++;
        parse = strtok (NULL, " ");
    }
    //Check if it is in the format "What is" or "Who is"
    if (((strcmp(blah_one,"What "))||(strcmp(blah_one,"Who ")))&&(strcmp(blah_two,"is m")))
    {
    	*tokens = ans;
    	strtok(*tokens,"\n"); //remove the new line
    }
    free(parse);
}

// Displays the game results for each player, their name and final score, ranked from first to last place
void show_results(player *players, int num_players)
{
	for (int i = 0; i<num_players; i++)
		printf("%s:	%d 	", players[i].name, players[i].score);
	printf("\n");
}



int main()
{
    // An array of 4 players, may need to be a pointer if you want it set dynamically
    player players[NUM_PLAYERS];
    int answered = 0;
    char *selected_player = calloc(BUFFER_LEN, sizeof(char));
    char *selected_category = calloc(BUFFER_LEN, sizeof(char));
    int selected_value;
    char *tokens;
    
    // Input buffer and and commands
    char buffer[BUFFER_LEN] = { 0 };

    system("clear");

    // Display the game introduction and initialize the questions
    initialize_game();

    // Prompt for players names
    // initialize each of the players in the array
    for (int i = 0; i < NUM_PLAYERS; i++)  {
		printf("Enter player %d's name: ",i + 1);
	    scanf("%s", players[i].name);
	    players[i].score = 0;
	}
    
	fputs("Enter any keys to START...", stdout);
    // Perform an infinite loop getting command input from users until game ends
    while (fgets(buffer, BUFFER_LEN, stdin) != NULL)
    {
    	system("clear");
        // Call functions from the questions and players source files
        if ((buffer[0] != '\n')) 
        { 
        	display_categories();	
        	fputs("Enter selected player: ",stdout);
        	fgets(buffer, BUFFER_LEN, stdin);
	    	strcpy(selected_player, buffer);
	    	strtok(selected_player,"\n"); //remove the newline

			if (player_exists(players, NUM_PLAYERS, selected_player))
	        {
	        	fputs("Choose a category: ",stdout);
	        	fgets(buffer, BUFFER_LEN, stdin); 
	        	strcpy(selected_category, buffer);
	        	strtok(selected_category, "\n");
				
				fputs("Choose a value: ",stdout);
				fgets(buffer, BUFFER_LEN, stdin);
	        	selected_value = atoi(buffer);
	        	
	        	if ((!already_answered(selected_category, selected_value)) && (question_exist(selected_category, selected_value)))
	        	{
	        		system("clear");
	        		printf("​Enter the answer starting with one of the following: ​what is​ or ​who is. \n");
	        		printf("Selected: %s %d \n", selected_category, selected_value);
	        		fputs("Question: ", stdout);
	        		display_question(selected_category, selected_value);
	        		fputs("Answer: ", stdout);
	        		fgets(buffer, BUFFER_LEN, stdin);
	        		tokenize(buffer, &tokens);
	        		printf("Entered answer: %s\n", tokens);

	        		if (valid_answer(selected_category, selected_value, tokens))
					{
						//update score
						answered++;
						update_score(players, NUM_PLAYERS, selected_player, selected_value);
						show_results(players,NUM_PLAYERS);
						if (answered < NUM_QUESTIONS)
							fputs("Enter any keys to continue...", stdout);
						else 
						{
							fputs("----------------------------------ENDED----------------------------------\n",stdout);
							break;
						}
					}
					else 
					{
						answered++;
						if (answered < NUM_QUESTIONS)
						fputs("Enter any keys to continue...", stdout);
						else 
						{
							fputs("----------------------------------ENDED----------------------------------\n",stdout);
							break;
						}
					}

	        	}  
	        	else 
	        	{ 
	        		system("clear");
	        		printf("That question has already been answered or doesn't exist!\n");
	        		fputs("Enter any keys to select a new question..", stdout);
	        	}
	        } 
	        else 
	        {
	        	system("clear");
	        	printf("The player you have entered does not exist!\n");
	        	fputs("Enter any keys to continue...", stdout);
	        }
    	}
    }
    system("clear");
    fputs("----------------------------------Results----------------------------------\n",stdout);
    player swap;
    int r = 1;
	for (int a = 0 ; a < ( NUM_PLAYERS - 1 ); a++)
	{
		for (int b = 0 ; b < NUM_PLAYERS - a - 1; b++)
		{
			if (players[b].score > players[b+1].score)
			{
				swap       = players[b];
				players[b]   = players[b+1];
				players[b+1] = swap;
			}
		}
	}
	for ( int i = NUM_PLAYERS - 1 ; i >= 0 ; i-- )
	{
    	printf("%d. 	%s 	%d\n", r, players[i].name, players[i].score);
    	r++;
	}

	printf("The winner is %s!!\n", players[NUM_PLAYERS-1].name);

    free(selected_player), free(selected_category);
    fputs("Enter any keys to EXIT...", stdout);
    fgets(buffer, BUFFER_LEN, stdin);
    return EXIT_SUCCESS;

}
