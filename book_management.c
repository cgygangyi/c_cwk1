#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "loans.h"
#include "reg_log.h"
#include "users.h"
#include "utility.h"



//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file, BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	while(head != NULL) {
		fprintf(file, "%d\n", head->id);
		fprintf(file, "%s\n", head->title);
		fprintf(file, "%s\n", head->authors);
		fprintf(file, "%d\n", head->year);
		fprintf(file, "%d\n", head->copies);
		if(head->borrowed_copies > 0){
			Loan *headl;
			headl = head->borrow->next;
			while(headl != NULL){
				fprintf(file, "%s", headl->loan_user);
				if(headl->next != NULL){
					fprintf(file, " ");
				}
				headl = headl->next;
			}
		}
		fprintf(file, "\n");
		if(head->next != NULL){
			fprintf(file, "\n");
		}
		head = head->next;
	}
	return 0;
}



//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookList *book_all) {
	if(file == NULL) {
		printf("\nError, books file does not exist.\n");
		exit(0);
	}

	Book *last;
	last = book_all->list;
	
	char StrLine[1024];
	while(!feof(file))
	{
		fgets(StrLine, 1024, file);
		if(!feof(file)){
			Book *p;
			p = (Book*)malloc(sizeof(Book));
			
			//load books information
			removeNewLine(StrLine);
			p->id = atoi(StrLine);
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->title = (char*)malloc(sizeof(char)*(strlen(StrLine)+1));
			strcpy(p->title, StrLine);
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->authors = (char*)malloc(sizeof(char)*(strlen(StrLine)+1));
			strcpy(p->authors, StrLine);
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->year = atoi(StrLine);
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->copies = atoi(StrLine);
			
			//load loans information
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->borrow = (Loan *)malloc(sizeof(Loan));
			p->borrowed_copies = 0;
			if(StrLine[0] != '\0'){
				char *token;
				token = strtok(StrLine, " ");
				Loan *pl, *lastl;
				lastl = p->borrow;
				while(token != NULL) {
					p->borrowed_copies ++;
					pl = (Loan *)malloc(sizeof(Loan));
					pl->loan_user = (char*)malloc(sizeof(char)*(strlen(token)+1));
					strcpy(pl->loan_user, token);
					lastl->next = pl;
					lastl = pl;
					token = strtok(NULL, " ");
				}
				lastl->next = NULL;
			}
			book_all->length ++;
			fgets(StrLine, 1024, file);
			last->next = p;
			last = p;
		}
		else {
			break;
		}
	}
	last->next = NULL;
	return 0;
}



//get the information of the book to be added.
//returns a book struct after getting the information, or NULL otherwise
Book *add_book_input() {
	Book *New;
	New = (Book *)malloc(sizeof(Book));
	char title[1024];
	char author[1024];
	char year[1024];
	char copies[1024];
	printf("Enter the title of your book you wish to add: ");
	fgets(title, 1024, stdin);
	removeNewLine(title);
	
	printf("Enter the author of your book you wish to add: ");
	fgets(author, 1024, stdin);
	removeNewLine(author);
	if(strlen(title) == 0 || strlen(author) == 0){
		printf("\nSorry, the title or author you entered is empty\n");
		New = NULL;
		return New;
	}

	printf("Enter the year that your book you wish to add was released: ");
	fgets(year, 1024, stdin);
	removeNewLine(year);
	if(checkNumber(year)){
		New = NULL;
		return New;
	}
	if(atoi(year) > 2022) {
		printf("\nSorry, it's only 2022.\n");
		New = NULL;
		return New;
	}
	printf("Enter the the number of copies of your book you wish to add: ");
	fgets(copies, 1024, stdin);
	removeNewLine(copies);
	if(checkNumber(copies)){
		New = NULL;
		return New;
	}
	
	New->title = (char*)malloc(sizeof(char)*(strlen(title)+1));
	New->authors = (char*)malloc(sizeof(char)*(strlen(author)+1));
	strcpy(New->title, title);
	strcpy(New->authors, author);
	New->year = atoi(year);
	New->copies = atoi(copies);
	New->next = NULL;
	return New;
}



//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book, BookList *book_all) {
	Book *head, *p;
	head = book_all->list;
	
	while(head->next != NULL){
		head = head->next;
		if(strcmp(head->title, book.title) == 0 && strcmp(head->authors, book.authors) == 0){
			printf("\nSorry, there is a same book.\n");
			return 1;
		}
	}
	p = (Book *)malloc(sizeof(Book));
	p->title = (char*)malloc(sizeof(char)*(strlen(book.title)+1));
	p->authors = (char*)malloc(sizeof(char)*(strlen(book.authors)+1));
	strcpy(p->title, book.title);
	strcpy(p->authors, book.authors);
	p->year = book.year;
	p->copies = book.copies;
	p->id = head->id + 1;
	p->borrow = (Loan *)malloc(sizeof(Loan));
	p->borrow->next = NULL;
	p->borrowed_copies = 0;
	head = book_all->list;
	while(head->next != NULL){
		head = head->next;
	}
	
	head->next = p;
	p->next = NULL;
	printf("\nSuccessfully add a book!\n");
	book_all->length ++;
	return 0;
}



//get the id of the book to be removed;
Book *remove_book_input() {
	Book *theBook;
	theBook = (Book *)malloc(sizeof(Book));
	char id[1024];
	printf("\nEnter the ID number of the book you wish to remove: ");
	fgets(id, 1024, stdin);
	removeNewLine(id);
	if(checkNumber(id)){
		theBook = NULL;
		return theBook;
	}
	theBook->id = atoi(id);
	theBook->next = NULL;
	return theBook;
}



//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book, BookList *book_all) {
	Book *head, *before, *change;
	head = book_all->list->next;
	before = book_all->list;
	while(head != NULL){
		if(head->id == book.id){
			if(head == book_all->list->next){
				book_all->list->next = head->next;
			}
			else {
				before->next = head->next;
			}
			change = head->next;
			while(change != NULL){
				change->id --;
				change = change->next;
			}
			free(head);
			printf("\nYou have successfully removed the book!\n");
			book_all->length --;
			return 0;
		}
		head = head->next;
		before = before->next;
	}
	printf("\nSorry, the option you entered was invalid, please try again.\n");
	return 1;
	
}



//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title, BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	
	BookList *byTitle;
	byTitle= (BookList *)malloc(sizeof(BookList));
	byTitle->list = (Book *)malloc(sizeof(Book));
	byTitle->length = 0;
	Book *p, *last;
	last = byTitle->list;
	
	while(head != NULL){
		if(strcmp(head->title, title) == 0){
			p = (Book *)malloc(sizeof(Book));
			p->title = (char*)malloc(sizeof(char)*(strlen(head->title)+1));
			p->authors = (char*)malloc(sizeof(char)*(strlen(head->authors)+1));
			p->id = head->id;
			strcpy(p->title, head->title);
			strcpy(p->authors, head->authors);
			p->year = head->year;
			p->id = head->id;
			p->copies = head->copies;
			last->next = p;
			last = p;
			byTitle->length++;
		}
		head = head->next;
	}
	last->next = NULL;
	if(byTitle->length == 0){
		byTitle->list = NULL;
	}
	
	return *byTitle;
}



//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author, BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	
	BookList *byAuthor;
	byAuthor= (BookList *)malloc(sizeof(BookList));
	byAuthor->list = (Book *)malloc(sizeof(Book));
	byAuthor->length = 0;
	Book *p, *last;
	last = byAuthor->list;
	
	while(head != NULL){
		if(strcmp(head->authors, author) == 0){
			p = (Book *)malloc(sizeof(Book));
			p->title = (char*)malloc(sizeof(char)*(strlen(head->title)+1));
			p->authors = (char*)malloc(sizeof(char)*(strlen(head->authors)+1));
			p->id = head->id;
			strcpy(p->title, head->title);
			strcpy(p->authors, head->authors);
			p->year = head->year;
			p->id = head->id;
			p->copies = head->copies;
			last->next = p;
			last = p;
			byAuthor->length++;
		}
		head = head->next;
	}
	last->next = NULL;
	if(byAuthor->length == 0){
		byAuthor->list = NULL;
	}
	
	return *byAuthor;
}



//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year, BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	
	BookList *byYear;
	byYear= (BookList *)malloc(sizeof(BookList));
	byYear->list = (Book *)malloc(sizeof(Book));
	byYear->length = 0;
	Book *p, *last;
	last = byYear->list;
	
	while(head != NULL){
		if(head->year == year){
			p = (Book *)malloc(sizeof(Book));
			p->title = (char*)malloc(sizeof(char)*(strlen(head->title)+1));
			p->authors = (char*)malloc(sizeof(char)*(strlen(head->authors)+1));
			p->id = head->id;
			strcpy(p->title, head->title);
			strcpy(p->authors, head->authors);
			p->year = head->year;
			p->id = head->id;
			p->copies = head->copies;
			last->next = p;
			last = p;
			byYear->length++;
		}
		head = head->next;
	}
	last->next = NULL;
	if(byYear->length == 0){
		byYear->list = NULL;
	}
	
	return *byYear;
}



//finds books with the given borrower.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_borrower (const char *borrower, BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	
	BookList *byBorrower;
	byBorrower = (BookList *)malloc(sizeof(BookList));
	byBorrower->list = (Book *)malloc(sizeof(Book));
	byBorrower->length = 0;
	Book *p, *last;
	last = byBorrower->list;
	
	Loan *headl;
	
	while(head != NULL){
		if(head->borrowed_copies > 0){
			headl = head->borrow->next;
			while(headl != NULL){
				if(strcmp(headl->loan_user, borrower) == 0){
					p = (Book *)malloc(sizeof(Book));
					p->title = (char*)malloc(sizeof(char)*(strlen(head->title)+1));
					p->authors = (char*)malloc(sizeof(char)*(strlen(head->authors)+1));
					p->id = head->id;
					strcpy(p->title, head->title);
					strcpy(p->authors, head->authors);
					p->year = head->year;
					p->id = head->id;
					p->copies = head->copies;
					last->next = p;
					last = p;
					byBorrower->length++;
					break;
				}
				headl = headl->next;
			}
		}
		head = head->next;
	}
	
	last->next = NULL;
	if(byBorrower->length == 0){
		byBorrower->list = NULL;
	}
	
	return *byBorrower;
}



//displays all the books or the books found in find_book_by function.
//returns 0 if the library has any book, or an error code otherwies.
//if borrow==1, copies items won't be displayed.
int display_found(BookList theBook, int borrow) {
	Book *head;
	if(theBook.list == NULL || theBook.list->next == NULL){
		printf("\nSorry, no book is found.\n");
		return 1;
	}
	else {
		int longestTitle = 0;
		int longestAuthors = 0;
		head = theBook.list->next;

		//get the length of the longest title and authors.
		while(head!=NULL)
		{
			if(strlen(head->title)>longestTitle) {
				longestTitle = strlen(head->title);
			}
			if(strlen(head->authors)>longestAuthors) {
				longestAuthors = strlen(head->authors);
			}
			head=head->next;
		}
		longestTitle += 7;
		longestAuthors += 8;
		head = theBook.list->next;
		printf("\n%-5s%s", "ID", "title");

		//fill in the blank to align the information to the left.
		for(int i = 0; i<longestTitle-strlen("title"); i++) {
			printf(" ");
		}
		printf("authors");
		for(int i = 0; i<longestAuthors-strlen("authors"); i++) {
			printf(" ");
		}
		if(borrow == 1) {
			printf("%-10s\n", "years");
		}
		else {
			printf("%-10s%-10s\n", "years", "copies");
		}
		while(head!=NULL)
		{
			printf("%-5d%s", head->id, head->title);
			for(int i = 0; i<longestTitle-strlen(head->title); i++) {
				printf(" ");
			}
			printf("%s", head->authors);
			for(int i = 0; i<longestAuthors-strlen(head->authors); i++) {
				printf(" ");
			}
			if(borrow == 1) {
				printf("%-10d\n", head->year);
			}
			else {
				printf("%-10d%-10d\n", head->year, head->copies);
			}
			head=head->next;
		}
		return 0;
	}
}




//Interface for searching books
void searchCLI(BookList *book_all) {
	int searching = 1;
	int option;
	char *information;
	information = (char*)malloc(sizeof(char)*1024);
	
	while( searching ){
		printf("\n Please choose an option:\n 1) Find books by title\n 2) Find books by author\n 3) Find books by year\n 4) Return to previews menu\n Option: ");
		option = optionChoice();
		
		if( option == 1 ) {
			printf("Please enter a title: ");
			fgets(information, 1024, stdin);
			removeNewLine(information);
			display_found(find_book_by_title(information, book_all), 0);
		}
		else if( option == 2 ) {
			printf("Please enter an author: ");
			fgets(information, 1024, stdin);
			removeNewLine(information);
			display_found(find_book_by_author(information, book_all), 0);
		}
		else if( option == 3 ) {
			printf("Please enter a year: ");
			fgets(information, 1024, stdin);
			removeNewLine(information);
			if(checkNumber(information) == 0){
				display_found(find_book_by_year(atoi(information), book_all), 0);
			}
		}
		else if( option == 4 ) {
			searching = 0;
			printf("\nReturn to previews menu...\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
	return;
}



//interface for the library
void libraryCLI(BookList* book_all, User *user_all) {
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
			if(name != NULL) {
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
			display_found(*book_all, 0);
		}
		else if( option == 5 ) {
			libraryOpen = 0;
			printf("\nThank you for using the library!\nGoodbye!\n");
		}
		else
			printf("\nSorry, the option you entered was invalid, please try again.\n");
	}
}



//saves the database of users in the specified file
//returns 0 if users were stored correctly, or an error code otherwise
int store_users(FILE *file, User *user_all) {
	User *head;
	head = user_all->next;
	while(head != NULL) {
		fprintf(file, "%s\n", head->username);
		fprintf(file, "%s\n", head->password);
		
		if(head->next != NULL){
			fprintf(file, "\n");
		}
		head = head->next;
	}
	return 0;
}



//loads the database of users from the specified file
//returns 0 if users were loaded correctly, or an error code otherwise
int load_users(FILE *file, User *user_all) {
	if( file == NULL) {
		printf("\nError, users file does not exist.\n");
		exit(0);
	}
	User *last;
	last = user_all;
	char StrLine[1024];
	while (!feof(file))
	{
		fgets(StrLine, 1024, file);
		if (!feof(file))
		{
			User *p;
			p=(User*)malloc(sizeof(User));
			
			removeNewLine(StrLine);
			p->username = (char*)malloc(sizeof(char)*(strlen(StrLine)+1));
			strcpy(p->username, StrLine);
			
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->password = (char*)malloc(sizeof(char)*(strlen(StrLine)+1));
			strcpy(p->password, StrLine);
			
			fgets(StrLine, 1024, file);
			last->next = p;
			last = p;
		}
		else
		{
			break;
		}
	}
	last->next=NULL;
	return 0;
}
