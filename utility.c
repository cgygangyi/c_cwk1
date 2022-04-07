#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"



// Utility functions to handle "safer" string input

// read in a line of text and convert to an integer option
int optionChoice( void ) {
    int option = -1;
    char line[80];

    // read in the current line as a string
    fgets(line,80,stdin);

    // atoi() converts string to integer, returns 0 if could not convert
    option = (int)atoi(line);

    return option;
}



// remove newline character from the fgets() input
void removeNewLine(char* string) {

    size_t length = strlen(string);

    if((length > 0) && (string[length-1] == '\n')) {
        string[length-1] ='\0';
    }
    return;
}



//check if the char is a natural number
//return 0 if it is a natural number, or an error code otherwise
int checkNumber(char* string) {
	if (strlen(string) == 0) {
		printf("\nSorry, the input must be a natural number.\n");
		return 1;
	}
	for(int i = 0; i < strlen(string); i++) {
		if (string[i] < 48 || string[i] > 57) {
			printf("\nSorry, the input must be a natural number.\n");
			return 1;
		}
	}
	return 0;
	
}

