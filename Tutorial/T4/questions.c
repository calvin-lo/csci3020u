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
#include "questions.h"
 #define MAX_LEN 256

// Initializes the array of questions for the game
void initialize_game(void)
{
    // initialize each question struct and assign it to the questions array
    //c1
    strcpy(questions[0].category, categories[0]); strcpy(questions[0].question, "Name a loop type that starts with W: ");  
    strcpy(questions[0].answer, "while"); questions[0].value  = 100; questions[0].answered = false;

    strcpy(questions[3].category, categories[0]); strcpy(questions[3].question, "These make code easily readable and understandable: ");  
    strcpy(questions[3].answer, "comments"); questions[3].value  = 200; questions[3].answered = false;
   
    strcpy(questions[6].category, categories[0]); strcpy(questions[6].question, "In the C programming language, these act much like objects: ");  
    strcpy(questions[6].answer, "structs");  questions[6].value  = 300; questions[6].answered = false;
    
    strcpy(questions[9].category, categories[0]); strcpy(questions[9].question, "A favorite topic amongst beginner programmers, these store memory address information: ");  
    strcpy(questions[9].answer, "pointers"); questions[9].value  = 400; questions[9].answered = false;

    //c2
    strcpy(questions[1].category, categories[1]); strcpy(questions[1].question, "This famous eccentric discovered a way to break German secret codes in World War II (last name only): ");  
    strcpy(questions[1].answer, "turing"); questions[1].value  = 100; questions[1].answered = false;

    strcpy(questions[4].category, categories[1]); strcpy(questions[4].question, "This \"tasty\" constant is the subject of many algorithms: ");  
    strcpy(questions[4].answer, "pi"); questions[4].value  = 200; questions[4].answered = false;

    strcpy(questions[7].category, categories[1]); strcpy(questions[7].question, "This Geometric algorithm involves subdividing a planar object in to triangles: ");  
    strcpy(questions[7].answer, "triangulation"); questions[7].value  = 300; questions[7].answered = false;
   
    strcpy(questions[10].category, categories[1]); strcpy(questions[10].question, "The answer to this question is \"algorithm\": ");  
    strcpy(questions[10].answer, "algorithm"); questions[10].value  = 400; questions[10].answered = false;
    
    //c3
    strcpy(questions[2].category, categories[2]); strcpy(questions[2].question, "The name of this Microsoft DBMS also means \"to gain entry\": ");  
    strcpy(questions[2].answer, "access"); questions[2].value  = 100; questions[2].answered = false;

    strcpy(questions[5].category, categories[2]); strcpy(questions[5].question, "This is the process of minimizing data redundancy in a database: ");  
	strcpy(questions[5].answer, "normalizatio"); questions[5].value  = 200; questions[5].answered = false;

    strcpy(questions[8].category, categories[2]); strcpy(questions[8].question, "This computer technology corporation shares a name with a character from \"The Matrix\" : ");  
    strcpy(questions[8].answer, "oracle"); questions[8].value  = 300; questions[8].answered = false;
   
    strcpy(questions[11].category, categories[2]); strcpy(questions[11].question, "This is the technical name for a row of data in a relational database: ");  
    strcpy(questions[11].answer, "tuple"); questions[11].value  = 400; questions[11].answered = false;

   	printf("THIS.....IS.....JEOPARDY!!!!!!!\nPlease welcome todays contestants!\n\n");

    
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
	printf("%s\t%s\t%s\n", categories[0], categories[1], categories[2]);

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
    	if (i % 3 == 0)
    	{
    		printf("\n");
    	}

    	if (questions[i].answered == false)
    	{
    		printf("   $%d   \t", questions[i].value);
    	}
    	else
    	{
    		printf("     X    \t");
    	}
    }

    printf("\n");
}
// Check question exist or not
bool question_exist(char *category, int value)  
{
	for (int i = 0; i < NUM_QUESTIONS; i++)  {
		if ((strcmp(questions[i].category,category) == 0) && (questions[i].value == value) )
			return true;
	}
	return false;
}
// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	//system("clear");
	for (int i = 0; i < NUM_QUESTIONS; i++)  {
		if ((strcmp(questions[i].category,category) == 0) && (questions[i].value == value) )
			printf("%s \n", questions[i].question);
	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
	int question_index = 0;

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
    	if (strcmp(questions[i].category, category) == 0 && questions[i].value == value)
    	{
    		question_index = i;
    		questions[i].answered = true;
    		break;
    	}
    }

    system("clear");

    if(strcmp(questions[question_index].answer, answer) == 0)
	{
		printf("That is correct! You received $%d!\n", value);
		return true;
	}
	else
	{
		printf("Your answer was incorrect or in the wrong format.\nThe answer was: %s\n", questions[question_index].answer);
		return false;
	}
}

// Returns true if the question has already been answered
bool already_answered(char *category, int value)
{
    // lookup the question and see if it's already been marked as answered
    for (int i = 0; i < 12; i++)  {
		if ((strcmp(questions[i].category,category) == 0) && (questions[i].value == value) && (questions[i].answered == true))
			return(true);
	}
    return false;
}


/*int main() {
	//test
	initialize_game();
	display_categories();
	display_question("c2",1);
	valid_answer("c2",1,"a4");
	questions[4].answered = true;
	already_answered("c2",1);
}*/