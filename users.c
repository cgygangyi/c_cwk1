#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "loans.h"
#include "utility.c"



void librarianCLI(BookList *book_all) {
	int librarianLoggedIn = 1;
	int option;
	Book *book;
	
	while( librarianLoggedIn ){
		printf("\n(logged in as librarian)");
		printf("\n Please choose an option:\n 1) Add a book\n 2) Remove a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			book = add_book_input();
			if(book != NULL) {
				add_book(*book, book_all);
			}
		}
		else if( option == 2 ) {
			display_all(book_all);
			book = remove_book_input();
			if(book != NULL){
				remove_book(*book, book_all);
			}
		}
		else if( option == 3 ) {
			searchCLI(book_all);
		}
		else if( option == 4 ) {
			display_all(book_all);
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

void userCLI(BookList *book_all, char *name) {
	int userLoggedIn = 1;
	int option;
	
	while( userLoggedIn ){
		printf("\n(logged in as: %s)", name);
		printf("\n Please choose an option:\n 1) Borrow a book\n 2) Return a book\n 3) Search for books\n 4) Display all books\n 5) Log out\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			borrow_book(name, book_all);
		}
		else if( option == 2 ) {
			return_book(name, book_all);
		}
		else if( option == 3 ) {
			searchCLI(book_all);
		}
		else if( option == 4 ) {
			display_all(book_all);
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

