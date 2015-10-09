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
#include "players.h"
#define MAX_LEN 256
// Returns true if the player name matches one of the existing players
bool player_exists(player *players, int num_players, char *name)
{
    
	for (int i = 0; i < num_players ; i++)  {
		if ((strcmp(players[i].name,name)) == 0)
			return true;
	}
    return false;
}

// Go through the list of players and update the score for the 
// player given their name
void update_score(player *players, int num_players, char *name, int score)
{
	for (int i = 0; i < num_players; i++)  {
		if ((strcmp(players[i].name,name)) == 0)  {
			players[i].score = score;
		}
	}
}

/*int main() {
	char name[MAX_LEN];
	int num_players = 4;
	player *players;
	players = (player *) malloc(num_players * sizeof(player));
	for (int i = 0; i < num_players; i++)  {
		printf("Enter player %d's name: ",i + 1);
	    scanf("%s", name);
	    strcpy(players[i].name, name);
	    players[i].score = 0;
	}
	player_exists(players,num_players,"b");
	update_score(players,num_players,"b", 100);
}*/