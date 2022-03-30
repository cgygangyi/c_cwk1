#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"



int main( int argc, char **argv )
{
	//dynamically allocates linked lists
	BookList *book_all;
	book_all = (BookList*)malloc(sizeof(BookList));
	book_all->length = 0;
	book_all->list = (Book*)malloc(sizeof(Book));
	
	User *user_all;
	user_all = (User*)malloc(sizeof(User));
	
	//Load books and user information
	FILE *fp;
	fp = fopen("books.txt", "r");
	load_books(fp, book_all);
	fclose(fp);

	fp = fopen("users.txt", "r");
	load_users(fp, user_all);
	fclose(fp);

	libraryCLI(book_all, user_all);

	//store books and user information
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
