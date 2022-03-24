#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

#define CreateNode(p)  p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p);

int load(FILE *file, Book theBook) {
	Book *p, *last;

	last = theBook.next;
	char StrLine[1024];
	while(!feof(file))
	{
		if(!feof(file)){
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p = (Book *)malloc(sizeof(Book));
			p->title = (char*)malloc(sizeof(char));
			p->authors = (char*)malloc(sizeof(char));
			p->id = atoi(StrLine);

			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			strcpy(p->title, StrLine);

			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			strcpy(p->authors, StrLine);

			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->year = atoi(StrLine);

			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p->copies = atoi(StrLine);
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

void print(Book theBook) {
	Book *head;
	head = theBook.next->next;
	printf("%-5s%-30s%-30s%-10s%-10s\n", "ID", "Title", "Authors", "years", "copies");
	while(head != NULL)
	{
		//printf("\n%s\n%s\n", head->username, head->password);
		printf("%-5d%-30s%-30s%-10d%-10d\n", head->id, head->title, head->authors, head->year, head->copies);
		head=head->next;
	}
}

int add_book(Book book) {
	Book *head, *New;
	char title[99];
	char author[99];
	char year[99];
	char copies[99];
	printf("Enter the title of your book you wish to add");
	gets(title);
	printf("Enter the author of your book you wish to add");
	gets(author);
	printf("Enter the year that your book you wish to add was released");
	gets(year);
	if(atoi(year) == 0){
		printf("year must be a number");
		return 1;
	}
	printf("Enter the the number of copies of your book you wish to add");
	gets(copies);
	if(atoi(copies) == 0){
		printf("copies must be a number");
		return 1;
	}
	New = (Book *)malloc(sizeof(Book));
	New->title = (char*)malloc(sizeof(char));
	New->authors = (char*)malloc(sizeof(char));
	strcpy(New->title, title);
	strcpy(New->authors, author);
	New->year = atoi(year);
	New->copies = atoi(copies);
	head = book.next;
	while(head->next != NULL){
		head = head->next;
	}
	New->id = head->id + 1;
	head->next = New;
	New->next = NULL;
}

int main(){
	Book theBook;
	theBook.next = (Book *)malloc(sizeof(Book));
	FILE *fp;
	fp = fopen("books.txt", "r");
	if( fp == NULL) {
		printf("\nError, user file does not exist.\n");
		exit(0);
	}
	load(fp, theBook);
	int fclose(FILE *fp);
	print(theBook);
	add_book(theBook);
	print(theBook);
}



void removeNewLine(char* string) {

	size_t length = strlen(string);

	if((length > 0) && (string[length-1] == '\n')) {
		string[length-1] ='\0';
	}
	return;
}
