//question 3

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int id, age, year; 
} student;

void save_student(student s) {
	FILE *fp = fopen("students.txt", "a");
	fprintf(fp, "%d,%d,%d \n", s.id, s.age, s.year);
	fclose(fp);
}

int main() {
	student s;
	printf("Enter your student id: ");
	scanf("%d", &s.id);
	printf("Enter your age: ");
	scanf("%d", &s.age);
	printf("Enter the year you start at UOIT: ");
	scanf("%d", &s.year);
	save_student(s);
}