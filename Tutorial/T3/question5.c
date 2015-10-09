//question 5

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define BUFFER 256

typedef struct {
	int student_id;
	int mark;
} grade;

void grade_students(grade *grades, int num_students)  {
	FILE *fp = fopen("grades.txt", "w");
	int sum = 0;
	for (int i = 0; i < num_students; i++) {
		sum = sum + grades[i].mark;
		fprintf(fp, "%d, %d \n", grades[i].student_id, grades[i].mark);
	}
	double avg = sum / num_students;
	int std_sum = 0; 
	double std = 0;
	for (int i = 0; i<num_students; i++)  {
		std_sum = std_sum + pow((grades[i].mark - avg),2);
	}
	
	std = sqrt(std_sum/(num_students-1));
	fprintf(fp, "Average: %lf, Standard deviation: %lf", avg, std);
}

int main() {
	char *professor;
	grade *grades;
	int num_students;
	professor = (char *) calloc(BUFFER, sizeof(char));
	printf("Enter your name: ");
	scanf("%s", professor);
	printf("Enter the number of students to mark: ");
	scanf("%d", &num_students);
	grades = (grade *) malloc(num_students * sizeof(grade));
	for (int i = 0; i < num_students; i++)
	{
	    printf("Enter the student id and the mark: ");
	    scanf("%d %d", &grades[i].student_id, &grades[i].mark);
	}
	grade_students(grades, num_students);
	free(professor), free(grades);
	
	
}