#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.c"


int borrow_book(Book book) {
	printf("\nEnter the ID number of the book you wish to borrow: ");
	printf("\nSorry, you already have a copy of this book on loan.\n");
	printf("\nSorry, the option you entered was invalid, please try again.\n");
	printf("\nYou have successfully borrowed the book!\n");
}



int return_book(Book book) {
	printf("\nBelow is the list of books you are currently borrowing:");
	printf("\nEnter the ID number of the book you wish to return: ");
	
	printf("\nSorry, the option you entered was invalid, please try again.\n");
	printf("\nReturned book successfully!\n");
}
