#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"
#include "account.h"

int main( int argc, char **argv )
{
	//load_books();
	//load_users(FILE *file);
	//load_loans(FILE *file);
	
	int libraryOpen = 1;
	int option;
	while( libraryOpen ){
		printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Search for books\n 4) Display all books\n 5) Quit\n Option: ");
		option = optionChoice();

		if( option == 1 ) {
			reg();
		}
		else if( option == 2 ) {
			login();
		}
		else if( option == 3 ) {
			printf("\nLogging search menu...\n");
			searchCLI();
		}
		else if( option == 4 ) {
			display_all();
		}
		else if( option == 5 ) {
			libraryOpen = 0;
			printf("\nThank you for using the library!\nGoodbye!\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}

	//store_books(FILE *file);
	//store_users(FILE *file);
	//store_loans(FILE *file);

	return 0;
}
