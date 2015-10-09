//question 4

#include <stdlib.h>
#include <stdio.h>

int main() {
	char *professor;
	int *student_ids, *grades;
	int num_students;
	professor = (char *) calloc(256, sizeof(char));
	printf("Enter your name: ");
	scanf("%s", professor);
	printf("Enter the number of students to mark: ");
	scanf("%d", &num_students);
	student_ids = (int *) malloc(sizeof(int));
	grades = (int *) malloc(sizeof(int));
	free(professor), free(student_ids), free(grades);
	
}