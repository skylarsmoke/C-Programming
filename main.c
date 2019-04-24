#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "class.h"


int main(void) {
	int answer;
	char time[20];
	char year[10];
	char day[3];
	// opens file
	FILE* file;
	char* filename = "../../../public/csci112sp19/pgm1/classes.txt";
	file = fopen(filename, "r");
	FILE* output = fopen("pgm1_output.txt", "w");
	// throws error if file isn't found
	classes_t cl[16];
	if (file == NULL) {
		printf("Error: File not found!\n");
		return(0);
	}

	int num_classes = scanClasses(file, cl);
	
	// while loop that keeps presenting questions
	while (answer != 5) {
		printf("1) Print all classes by CSCI number in order of CSCI number\n");
		printf("2) Print all classes available on MWF or available on TR in order of times\n");
		printf("3) Print classes available at a specific day and time\n");
		printf("4) Print classes available to Freshman, Sophomore, Junior, or Senior\n");
		printf("5) Quit\n");
		printf("Selection: ");
		if (scanf("%d", &answer) != 1) {
			printf("Please enter a valid menu option!\n");
			return(0);
		}
		printf("\n");
		
		if (answer > 5 || answer < 1) {
			printf("Please enter a valid menu option!\n");
			return(0);
		}
		// switch statement that goes to the correct function based off of the menu choice
		switch(answer) {
			case 1:
				fprintf(output, "All Classes By Class Number\n");
				printAllByNumber(num_classes, cl, output);
				break;
			case 2:
				printf("MWF or TR?");
				scanf("%s", day);
				for (int i = 0; day[i]; i++) {
					day[i] = toupper(day[i]);
				}
				if (strcmp(day, "MWF") != 0 && strcmp(day, "TR") != 0) {
					printf("Please enter a valid menu option!\n");
					return(0);
				}
				fprintf(output, "All Classes on %s\n", day);
				printAllMWF(num_classes, cl, output, day);
				break;
			case 3:
				printf("Time? ");
				getchar();
				fgets(time, 20, stdin);
				for (int i = 0; time[i]; i++) {
					time[i] = toupper(time[i]);
				}
				fprintf(output, "All Classes at %s", time);
				printSpecTime(num_classes, cl, time, output);
				break;
			case 4:
				printf("Year? ");
				scanf("%s", year);
				for (int i = 0; year[i]; i++) {
					year[i] = tolower(year[i]);
				}
				fprintf(output, "Classes offered to %s\n", year);
				if (strcmp("freshman", year) == 0) {
					printClassesByYear(num_classes, cl, 1, output);
				} else if (strcmp("sophomore", year) == 0) {
					printClassesByYear(num_classes, cl, 2, output);
				} else if (strcmp("junior", year) == 0) {
					printClassesByYear(num_classes, cl, 3, output);
				} else if (strcmp("senior", year) == 0) {
					printClassesByYear(num_classes, cl, 4, output);
				} else {
					printf("Please enter either Freshman, Sophomore, Junior, or Senior.\n");
					return(0);
				}
				fprintf(output, "\n");
				break;
		}

	}

	return(0);
}

