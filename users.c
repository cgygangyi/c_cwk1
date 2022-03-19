#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.c"



void librarianCLI() {
	int librarianLoggedIn = 1;
	int option;
	
	while( librarianLoggedIn ){
		printf("\n Please choose an option:\n 1) Add a book\n 2) Remove a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			add_book(Book book);
		}
		else if( option == 2 ) {
			remove_book(Book book);
		}
		else if( option == 3 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 4 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 5 ) {
			librarianLoggedIn = 0;
			printf("\nLogging out...\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
	return;
}

void userCLI() {
	int userLoggedIn = 1;
	int option;
	
	while( userLoggedIn ){
		printf("\n Please choose an option:\n 1) Borrow a book\n 2) Return a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			add_book(Book book);
		}
		else if( option == 2 ) {
			remove_book(Book book);
		}
		else if( option == 3 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 4 ) {
			printf("\nLibrarian login\n");
		}
		else if( option == 5 ) {
			userLoggedIn = 0;
			printf("\nLogging out...\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
	return;
}

