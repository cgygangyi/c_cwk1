
#ifndef BOOK_MANAGEMENT_GUARD__H
#define BOOK_MANAGEMENT_GUARD__H

#include <stdio.h>

/*You can extend the structs (Book and BookList) defined in this head file;
  However, you may not change the function prototypes.
  You are also free to add additional head files and data structures as needed.
*/


typedef struct _Loan {
	char *loan_user;
	struct _Loan *next; //pointer to the next loan element
}Loan;

typedef struct _Book {
	unsigned int id; //Book ID
	char *title; //book titlechar *title; //book title
	char *authors; //comma separated list of authors
	unsigned int year; // year of publication
	unsigned int copies; //number of copies the library has
	unsigned int borrowed_copies; //number of users who have borrowed this book.
	struct _Loan *borrow; //pointer to the loan struct
	struct _Book *next; //pointer to the next book element
}Book;


typedef struct _BookList {
	Book* list; // pointer to a list of struct Book.
	unsigned int length; // number of elements in the (Book*) List
}BookList;


//saves the database of books in the specified file
//returns 0 if books were stored correctly, or an error code otherwise
int store_books(FILE *file);

//loads the database of books from the specified file
//the file must have been generated by a previous call to store_books()
//returns 0 if books were loaded correctly, or an error code otherwise
int load_books(FILE *file, BookList *book_all);

//adds a book to the ones available to the library
//returns 0 if the book could be added, or an error code otherwise
int add_book(Book book, BookList *book_all);

Book *add_book_input();

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(Book book, BookList *book_all);

//finds books with a given title.
//returns a BookList structure, where the field "list" is a list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_title (const char *title, BookList *book_all);

//finds books with the given authors.
//returns a Booklist structure, where the field "list" is a newly allocated list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_author (const char *author, BookList *book_all);

//finds books published in the given year.
//returns a Booklist structure, where the field "list" is a list of books, or null if no book with the
//provided title can be found. The length of the list is also recorded in the returned structure, with 0 in case
//list is the NULL pointer.
BookList find_book_by_year (unsigned int year, BookList *book_all);

void display_all(BookList *book_all);



void searchCLI(BookList *book_all);





typedef struct _User {
	char *username;
	char *password;
	struct _User *next; //pointer to the next user element
}User;


typedef struct _UserList {
	User* list; // pointer to a list of struct User.

}UserList;




int store_users(FILE *file);
int load_users(FILE *file, UserList *user_all);


#endif
