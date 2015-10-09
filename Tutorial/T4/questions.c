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
    strcpy(questions[0].category, categories[0]); strcpy(questions[0].question, "q0");  strcpy(questions[0].answer, "a0");
    questions[0].value  = 1; questions[0].answered = false;

    strcpy(questions[1].category, categories[0]); strcpy(questions[1].question, "q1");  strcpy(questions[1].answer, "a1");
    questions[1].value  = 2; questions[1].answered = false;
   
    strcpy(questions[2].category, categories[0]); strcpy(questions[2].question, "q2");  strcpy(questions[2].answer, "a2");
    questions[2].value  = 3; questions[2].answered = false;
    
    strcpy(questions[3].category, categories[0]); strcpy(questions[3].question, "q3");  strcpy(questions[3].answer, "a3");
    questions[3].value  = 4; questions[3].answered = false;

    //c2
    strcpy(questions[4].category, categories[1]); strcpy(questions[4].question, "q4");  strcpy(questions[4].answer, "a4");
    questions[4].value  = 1; questions[4].answered = false;

    strcpy(questions[5].category, categories[1]); strcpy(questions[5].question, "q5");  strcpy(questions[5].answer, "a5");
    questions[5].value  = 2; questions[5].answered = false;

    strcpy(questions[6].category, categories[1]); strcpy(questions[6].question, "q6");  strcpy(questions[6].answer, "a6");
    questions[6].value  = 3; questions[6].answered = false;
   
    strcpy(questions[7].category, categories[1]); strcpy(questions[7].question, "q7");  strcpy(questions[2].answer, "a7");
    questions[7].value  = 4; questions[7].answered = false;
    
    //c3
    strcpy(questions[8].category, categories[2]); strcpy(questions[8].question, "q8");  strcpy(questions[8].answer, "a8");
    questions[8].value  = 1; questions[8].answered = false;

    strcpy(questions[9].category, categories[2]); strcpy(questions[9].question, "q9");  strcpy(questions[9].answer, "a9");
    questions[9].value  = 2; questions[9].answered = false;

    strcpy(questions[10].category, categories[2]); strcpy(questions[10].question, "q10");  strcpy(questions[10].answer, "a10");
    questions[10].value  = 3; questions[10].answered = false;
   
    strcpy(questions[11].category, categories[2]); strcpy(questions[11].question, "q11");  strcpy(questions[11].answer, "a11");
    questions[11].value  = 4; questions[11].answered = false;



    
}

// Displays each of the remaining categories and question dollar values that have not been answered
void display_categories(void)
{
    // print categories and dollar values for each unanswered question in questions array
    for (int i = 0; i < 12; i++)  {
    	if (questions[i].answered == false)  
    		printf("categories: %s		Value: %d \n", questions[i].category, questions[i].value);
    }
}

// Displays the question for the category and dollar value
void display_question(char *category, int value)
{
	for (int i = 0; i < 12; i++)  {
		if ((strcmp(questions[i].category,category) == 0) && (questions[i].value == value) )
			printf("question: %s \n", questions[i].question);
	}
}

// Returns true if the answer is correct for the question for that category and dollar value
bool valid_answer(char *category, int value, char *answer)
{
    // Look into string comparison functions
    for (int i = 0; i < 12; i++)  {
		if ((strcmp(questions[i].category,category) == 0) && (questions[i].value == value) && (strcmp(questions[i].answer,answer) ==0))
			return true;
	}
    return false;
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