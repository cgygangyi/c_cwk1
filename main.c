#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"
#include "reg_log.h"
#include "users.h"

int main( int argc, char **argv )
{
	
	Book *book_all;
	book_all = (Book*)malloc(sizeof(Book));
	
	User *user_all;
	user_all = (User*)malloc(sizeof(User));
	
	FILE *fp;
	
	fp = fopen("books.txt", "r");
	if(fp == NULL) {
		printf("\nError, books file does not exist.\n");
		exit(0);
	}
	load_books(fp, book_all);
	fclose(fp);
	
	fp = fopen("users.txt", "r");
	if( fp == NULL) {
		printf("\nError, users file does not exist.\n");
		exit(0);
	}
	load_users(fp, user_all);
	fclose(fp);
	
	
	int libraryOpen = 1;
	int option;
	while( libraryOpen ){
		printf("\n Please choose an option:\n 1) Register an account\n 2) Login\n 3) Search for books\n 4) Display all books\n 5) Quit\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			reg(user_all);
		}
		else if( option == 2 ) {
			char *name;
			name = (char*)malloc(sizeof(char)*1024);
			name = login(user_all);
			if(name == NULL) {
				//TODO
			}
			else {
				if(strcmp(name, "librarian") == 0){
					librarianCLI(book_all);
				}
				else{
					userCLI(book_all, name);
				}
			}
			
		}
		else if( option == 3 ) {
			printf("\nLogging search menu...\n");
			searchCLI(book_all);
		}
		else if( option == 4 ) {
			display_all(book_all);
		}
		else if( option == 5 ) {
			libraryOpen = 0;
			printf("\nThank you for using the library!\nGoodbye!\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
	
	
	fp = fopen("books.txt", "w+");
	store_books(fp, book_all);
	fclose(fp);

	fp = fopen("users.txt", "w+");
	store_users(fp, user_all);
	fclose(fp);

	free(book_all);
	free(user_all);
	
	
	return 0;
}
