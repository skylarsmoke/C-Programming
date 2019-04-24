#include <stdio.h>

// creates a data structure for each class
typedef struct {
	char name[100];
	char number[10];
	char time[10];
	char days[5];
	int year;
} classes_t;

// declares classes
int scanClasses(FILE*, classes_t cl[]);
void printAllByNumber(int, classes_t cl[], FILE*);
void printAllMWF(int, classes_t cl[], FILE*, char day[]);
void printSpecTime(int, classes_t cl[], char usertime[], FILE*);
void printClassesByYear(int, classes_t cl[], int, FILE*);
