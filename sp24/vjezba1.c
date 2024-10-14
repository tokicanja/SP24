#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define ERROR_OPENING_FILE -1
#define BUFFER_SIZE 1024
#define MAX_SIZE 50

typedef struct {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int count_rows(char* filename);
Student* memoryAllocation(int n);
int loadingData(char* filename, Student* s, int n);
double max_points(Student* s, int n);
int printData(Student* s, int n, double max_points);

int main()
{
	char filename[] = "Studenti.txt";

	int n = count_rows(filename);
	if (n == ERROR_OPENING_FILE)
	{
		return ERROR_OPENING_FILE;
	}

	Student* s = memoryAllocation(n);
	if (s == NULL)
	{
		return ERROR_OPENING_FILE;
	}

	if (loadingData(filename, s, n) == ERROR_OPENING_FILE)
	{
		free(s);
		return ERROR_OPENING_FILE;
	}

	double maxPts = max_points(s, n);

	printData(s, n, maxPts);

	free(s);

	return 0;
}

int count_rows(char* filename)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return ERROR_OPENING_FILE;
	}

	char buffer[BUFFER_SIZE] = { 0 };
	int count = 0;

	while (!feof(fp))
	{
		fgets(buffer, BUFFER_SIZE, fp);
		count++;
	}

	fclose(fp);
	return count;
}

Student* memoryAllocation(int n)
{
	Student* s = (Student*)malloc(n * sizeof(Student));
	if (s == NULL)
	{
		printf("Memory allocation failed!\n");
		return NULL;
	}
	return s;
}

int loadingData(char* filename, Student* s, int n)
{
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		free(s);
		return ERROR_OPENING_FILE;
	}

	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%s %s %lf", s[i].name, s[i].surname, &s[i].points);
	}

	fclose(fp);
	return 0;
}

double max_points(Student* s, int n)
{
	double max_points = 0.0;
	for (int i = 0; i < n; i++)
	{
		if (s[i].points > max_points)
		{
			max_points = s[i].points;
		}
	}
	return max_points;
}

int printData(Student* s, int n, double max_points)
{
	printf("IME\tPREZIME\tAPSOLUTNI BODOVI\tRELATIVNI BODOVI\n");
	for (int i = 0; i < n; i++)
	{
		printf("%s\t%s\t%.2lf\t\t\t%.2lf%%\n", s[i].name, s[i].surname, s[i].points, (s[i].points / max_points) * 100);
	}
	return 0;
}