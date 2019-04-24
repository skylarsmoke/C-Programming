#include <stdio.h>
#include <string.h>
#include "class.h"

// scans lines of file and puts respective info into data structure
int scanClasses(FILE* file, classes_t cl[]) {
	char line[100];
	char copyLine[100];
	char *current;
	int i = 0;
	while (fgets(line, sizeof(line), file)) {
		strcpy(copyLine, line);
		current = strtok(copyLine, " ");
		sscanf(current, "%s", cl[i].number);
		current = strtok(NULL, "$");
		strcpy(cl[i].name, current);
		current = strtok(NULL, " ");
		sscanf(current, "%s", cl[i].days);
		current = strtok(NULL, " ");
		sscanf(current, "%s", cl[i].time);
		current = strtok(NULL, " ");
		sscanf(current, "%d", &cl[i].year); 
		//printf("%s %s %s %s %d\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time, cl[i].year);
		i++;
	}
	
	return i;
}

// prints all classes by number in order
void printAllByNumber(int n, classes_t cl[], FILE* output) {
	
	// swaps the classes if the number of the class is bigger than the other	
	classes_t temp;
	int i, j, swap = 0;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			swap = strncmp(cl[i].number + 4, cl[j].number + 4, 3);
			
			if (swap < 0) {
				temp = cl[i];
				cl[i] = cl[j];
				cl[j] = temp;
			}
		}
		
	}
	
	// prints classes and decides what year can take it
	for (int y = 0; y < i; y++) {
		if (cl[y].year == 1) {
			printf("%s\b, %s, %s, %s, Freshman\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Freshman\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
		}
		
		if (cl[y].year == 2) {
			printf("%s\b, %s, %s, %s, Sophomore\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Sophomore\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
		}	
		
		if (cl[y].year == 3) {
			printf("%s\b, %s, %s, %s, Junior\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Junior\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
		}	
		
		if (cl[y].year == 4) {
			printf("%s\b, %s, %s, %s, Senior\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Senior\n", cl[y].name, cl[y].number, cl[y].days, cl[y].time);
		}
			
	}
	printf("\n");
	fprintf(output, "\n");	
}

// prints all classes on certain days and sorts by time
void printAllMWF(int n, classes_t cl[], FILE* output, char day[]) {
        
	classes_t check[10];
	int x = 0, i = 0;
	// checks if the day of a class matches and puts it into another array
	for (i = 0; i < n; i++) {
		if (strcmp(cl[i].days, day) == 0) {
			check[x] = cl[i];
			x++;
		}
	}
        
	// sorts new array by time	
	classes_t temp;
	int j, z, swap = 0;
	for (j = 0; j < x; j++) {
		for (z = 0; z < x; z++) {
			swap = strncmp(check[j].time, check[z].time, 2);
			if (swap < 0) {
				temp = check[j];
				check[j] = check[z];
				check[z] = temp;
			}
		}
	}
       
        printf("\n");
	// prints classes in the new array       
	for (int y = 0; y < x; y++) {
		if (check[y].year == 1) {
			printf("%s\b, %s, %s, %s, Freshman\n", check[y].name, check[y].number, check[y].days, check[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Freshman\n", check[y].name, check[y].number, check[y].days, check[y].time);
		}
		else if (check[y].year == 2) {
			printf("%s\b, %s, %s, %s, Sophomore\n", check[y].name, check[y].number, check[y].days, check[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Sophomore\n", check[y].name, check[y].number, check[y].days, check[y].time);
		}
		else if (check[y].year == 3) {
			printf("%s\b, %s, %s, %s, Junior\n", check[y].name, check[y].number, check[y].days, check[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Junior\n", check[y].name, check[y].number, check[y].days, check[y].time);
		}
		else if (check[y].year == 4) {
			printf("%s\b, %s, %s, %s, Senior\n", check[y].name, check[y].number, check[y].days, check[y].time);
			fprintf(output, "%-47s\b %s, %s, %s, Senior\n", check[y].name, check[y].number, check[y].days, check[y].time);
		}
	}
	printf("\n");
	fprintf(output, "\n");
}

// prints the classes at an inputted time
void printSpecTime(int n, classes_t cl[], char usertime[], FILE* output) {
	// checks if the days match
	classes_t check[10];
	int i = 0, x = 0;
	for (i = 0; i < n; i++) {
		if (strncmp(cl[i].days, usertime, 2) == 0) {
			check[x] = cl[i];
			x++;
		}
	}
	char* result;
	strtok(usertime, " ");
	result = strtok(NULL, "\0");
	// prints the class if the time matches
	for (int y = 0; y < x; y++) {
		if (strncmp(check[y].time, result, 2) == 0) {
			if (check[y].year == 1) {
				printf("%s\b, %s, %s, %s, Freshman\n", check[y].name, check[y].number, check[y].days, check[y].time);
				fprintf(output, "%-47s\b %s, %s, %s, Freshman\n", check[y].name, check[y].number, check[y].days, check[y].time);
			}
			if (check[y].year == 2) {
				printf("%s\b, %s, %s, %s, Sophomore\n", check[y].name, check[y].number, check[y].days, check[y].time);
				fprintf(output, "%-47s\b %s, %s, %s, Sophomore\n", check[y].name, check[y].number, check[y].days, check[y].time);
			}
			if (check[y].year == 3) {
				printf("%s\b, %s, %s, %s, Junior\n", check[y].name, check[y].number, check[y].days, check[y].time);
				fprintf(output, "%-47s\b %s, %s, %s, Junior\n", check[y].name, check[y].number, check[y].days, check[y].time);
			}
			if (check[y].year == 4) {
				printf("%s\b, %s, %s, %s, Senior\n", check[y].name, check[y].number, check[y].days, check[y].time);
				fprintf(output, "%-47s\b %s, %s, %s, Senior\n", check[y].name, check[y].number, check[y].days, check[y].time);
			}
		}
	}
	printf("\n");
	fprintf(output, "\n");
}
	


void printClassesByYear(int n, classes_t cl[], int year, FILE* output) {
	// prints class if the year matches
	for (int i = 0; i < n; i++) {
		if(year == 1) {
			if (cl[i].year == year) {
				printf("%s\b, %s, %s, %s, Freshman\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
				fprintf(output, "%-47s\b %s, %s, %s, Freshman\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
			}
			
		}
		
		if(year == 2) {
			if (cl[i].year == year) {
				printf("%s\b, %s, %s, %s, Sophomore\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
				fprintf(output, "%-47s\b %s, %s, %s, Sophomore\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
			}
			
		}
		if(year == 3) {
			if (cl[i].year == year) {
				printf("%s\b, %s, %s, %s, Junior\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
				fprintf(output, "%-47s\b %s, %s, %s, Junior\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
			}
			
		}
		if(year == 4) {
			if (cl[i].year == year) {
				printf("%s\b, %s, %s, %s, Senior\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
				fprintf(output, "%-47s\b %s, %s, %s, Senior\n", cl[i].name, cl[i].number, cl[i].days, cl[i].time);
			}
			
		}
	}	
	printf("\n");
	fprintf(output, "\n");
}

