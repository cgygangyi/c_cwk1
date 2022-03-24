#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

#define CreateNode(p)  p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p);

int load(FILE *file, BookList *book_all) {
	Book *p, *last;

	last = book_all->list;
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

void print(BookList *book_all) {
	Book *head;
	head = book_all->list->next;
	printf("%-5s%-30s%-30s%-10s%-10s\n", "ID", "Title", "Authors", "years", "copies");
	while(head != NULL)
	{
		//printf("\n%s\n%s\n", head->username, head->password);
		printf("%-5d%-30s%-30s%-10d%-10d\n", head->id, head->title, head->authors, head->year, head->copies);
		head=head->next;
	}
}

/*void print2(BookList theBook) {
	Book *head;
	head = theBook.list->next->next;
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

BookList find_book_by_title (const char *title, Book book) {
	Book *head;
	head = book.next->next;
	
	BookList byTitle;
	byTitle.list->next = (Book *)malloc(sizeof(Book));
	byTitle.length = 0;
	Book *p, *last;
	last = byTitle.list->next;
	
	while(head != NULL){
		if(strcmp(head->title, title) == 0){
			p = (Book *)malloc(sizeof(Book));
			p->title = (char*)malloc(sizeof(char));
			p->authors = (char*)malloc(sizeof(char));
			p->id = head->id;
			strcpy(p->title, head->title);
			strcpy(p->authors, head->authors);
			p->year = head->year;
			p->id = head->id;
			last->next = p;
			last = p;
			byTitle.length++;
		}
		head = head->next;
	}
	last->next = NULL;
	
	return byTitle;
}*/

int main(){
	BookList *book_all;
	book_all = (BookList *)malloc(sizeof(BookList));
	book_all->list = (Book *)malloc(sizeof(Book));
	BookList found;
	FILE *fp;
	fp = fopen("books.txt", "r");
	if( fp == NULL) {
		printf("\nError, user file does not exist.\n");
		exit(0);
	}
	load(fp, book_all);
	int fclose(FILE *fp);
	print(book_all);
	//add_book(theBook);
	//print(theBook);
	//char *title;
	//title = (char *)malloc(sizeof(char)*80);
	//printf("enter");
	//gets(title);
	//found = find_book_by_title (title, theBook);
	//print2(found);
}



void removeNewLine(char* string) {

	size_t length = strlen(string);

	if((length > 0) && (string[length-1] == '\n')) {
		string[length-1] ='\0';
	}
	return;
}
