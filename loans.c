#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"



//a specific user borrows a book from the library
//returns 0 if books were borrowed successfully, or an error code otherwise
int borrow_book(const char *username, BookList *book_all) {
	char id[1024];
	printf("\nEnter the ID number of the book you wish to loan: ");
	fgets(id, 1024, stdin);
	removeNewLine(id);
	if(checkNumber(id)){
		return 1;
	}
	Book *head;
	head = book_all->list->next;
	while(head != NULL){
		if(head->id == atoi(id)){
			if(head->copies == 0) {
				printf("\nSorry, this book doesn't have extra copy.\n");
				return 1;
			}
			Loan *p, *last;
			last = head->borrow->next;
			while(last != NULL){
				if(strcmp(last->loan_user, username) == 0){
					printf("\nSorry, you already have a copy of this book on loan.\n");
					return 1;
				}
				last = last->next;
			}
			p = (Loan *)malloc(sizeof(Loan));
			p->loan_user = (char*)malloc(sizeof(char)*(strlen(username)+1));
			strcpy(p->loan_user, username);
			last = head->borrow;
			while(last->next != NULL){
				last = last->next;
			}
			last->next = p;
			p->next = NULL;
			head->borrowed_copies ++;
			head->copies --;
			printf("\nYou have successfully borrowed the book!\n");
			return 0;
		}
		head = head->next;
	}
	
	printf("\nSorry, the option you entered was invalid, please try again.\n");
	return 1;
}



//a specific user returns a book to the library
//returns 0 if books were returned successfully, or an error code otherwise
int return_book(const char *username, BookList *book_all) {
	BookList foundbook;
	foundbook = find_book_by_borrower (username, book_all);
	if(foundbook.list == NULL){
		printf("\nSorry, you haven't borrowed any book.\n");
		return 1;
	}
	else {
		printf("\nBelow is the list of books you are currently borrowing:");
		display_found(foundbook, 1);
	}
	
	char id[1024];
	printf("\nEnter the ID number of the book you wish to return: ");
	fgets(id, 1024, stdin);
	removeNewLine(id);
	
	if(checkNumber(id)){
		return 1;
	}
	
	Book *head;
	Loan *headl, *before;
	head = book_all->list->next;
	while(head != NULL){
		if(head->id == atoi(id)){
			headl = head->borrow->next;
			before = head->borrow;
			while(headl != NULL){
				if(strcmp(headl->loan_user, username) == 0){
					if(headl == head->borrow->next){
						head->borrow->next = headl->next;
					}
					else{
						before->next = headl->next;
					}
					free(headl);
					printf("\nReturned book successfully!\n");
					head->copies ++;
					return 0;
				}
				headl = headl->next;
				before = before->next;
			}
		}
		head = head->next;
	}
	printf("\nSorry, the option you entered was invalid, please try again.\n");
	return 1;
}
