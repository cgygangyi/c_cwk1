#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.c"

int main( int argc, char **argv )
{
	//load_books('books.txt');
	int libraryOpen = 1;
	int option;
	while( libraryOpen ){
		printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Search for books\n 4) Display all books\n 5) Quit\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			printf("\nUser login\n");
		}
		else if( option == 2 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 3 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 4 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 5 ) {
			libraryOpen = 0;
			printf("\nThank you for using the library!\nGoodbye!\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
	
	//store_books(FILE *file);
	
	return 0;
}
