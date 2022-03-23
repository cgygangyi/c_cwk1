#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"
#include "reg_log.h"
#include "users.h"

int main( int argc, char **argv )
{
	Book book;
	book.next = (Book *)malloc(sizeof(Book));
	User user;
	user.next = (User *)malloc(sizeof(User));
	FILE *fp;

	fp = fopen("books.txt", "r");
	if( fp == NULL) {
		printf("\nError, book file does not exist.\n");
		exit(0);
	}
	load_books(fp, book);
	int fclose(FILE *fp);

	fp = fopen("users.txt", "r");
	if( fp == NULL) {
		printf("\nError, user file does not exist.\n");
		exit(0);
	}
	load_users(fp, user);
	int fclose(FILE *fp);

	load_loans(fp);

	int libraryOpen = 1;
	int option;
	while( libraryOpen ){
		printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Search for books\n 4) Display all books\n 5) Quit\n Option: ");
		option = optionChoice();

		if( option == 1 ) {
			reg(user);
		}
		else if( option == 2 ) {
			User *name;
			name = login(user);
			if(strcmp(name->username, "librarian")){
				librarianCLI();
			}
			else if(name){
				userCLI(name);
			}
		}
		else if( option == 3 ) {
			printf("\nLogging search menu...\n");
			searchCLI();
		}
		else if( option == 4 ) {
			display_all(book);
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
