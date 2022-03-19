#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char **argv )
{
	char bookFile[40];

	if(argc != 2){
		printf("Error\nExpected use: ./library books.txt\n");
		return 0;
	}

	strcpy(bookFile, argv[1]);

	printf("\nIntialising library system!\n");
	libraryCLI( bookFile );
	printf("\nClosing library system!\n\n");

	return 0;
}


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
