#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

#define CreateNode(p)  p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p);

int load(FILE *file) {
	User *h, *p, *last;
	h = (User *)malloc(sizeof(User));
	last = h;
	UserList users;
	users.length = 0;
	users.list = h;
	
	char StrLine[1024];
	while(!feof(file))
	{
		if(!feof(file)){
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			p = (User *)malloc(sizeof(User));
			p->username = (char*)malloc(sizeof(char));
			p->password = (char*)malloc(sizeof(char));
			
			strcpy(p->username, StrLine);
			
			fgets(StrLine, 1024, file);
			removeNewLine(StrLine);
			strcpy(p->password, StrLine);
			
			last->next = p;
			last = p;
			users.length++;
		}
		else {
			break;
		}
	}
	last->next = NULL;
	User *head;
	head = users.list->next;
	while(head!=NULL)
	{
		printf("\n%s\n%s\n", head->username, head->password);
		//printf("%d\n%s\n%s\n%d\n%d\n", head->id, head->title, head->authors, head->year, head->copies);
		head=head->next;
	}
	return 0;
}




int main(){
	FILE *fp;
	fp = fopen("users.txt", "r");
	if( fp == NULL) {
		printf("\nError, user file does not exist.\n");
		exit(0);
	}
	load(fp);
	int fclose(FILE *fp);
}



void removeNewLine(char* string) {

	size_t length = strlen(string);

	if((length > 0) && (string[length-1] == '\n')) {
		string[length-1] ='\0';
	}
	return;
}
