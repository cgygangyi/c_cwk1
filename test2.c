#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "utility.h"

#define CreateNode(p)  p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p)   free((void *)p);

int load_users(FILE *file, UserList *user_all) {
	User *p, *last;
	last = user_all->list;
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
		}
		else {
			break;
		}
	}
	last->next = NULL;
	return 0;
}

int reg(UserList *user_all) {
	char enteredname[30];
	char enteredpass[30];
	
	User *head, *New;
	head = user_all->list;
	printf("\nPlease enter a username: ");
	gets(enteredname);
	if(strcmp(enteredname, "librarian")==0){
		printf("\nSorry, registration unsuccessful, the username you entered already exists.\n");
		return 1;
	}
	while(head != NULL){
		if(strcmp(head->username, enteredname)==0){
			printf("\nSorry, registration unsuccessful, the username you entered already exists.\n");
			return 1;
		}
		head = head->next;
	}
	printf("\nPlease enter a passward: ");
	gets(enteredpass);
	New = (User *)malloc(sizeof(User));
	New->username = (char*)malloc(sizeof(char));
	New->password = (char*)malloc(sizeof(char));
	strcpy(New->username, enteredname);
	strcpy(New->password, enteredpass);
	head = user_all->list;
	while(head->next != NULL){
		head = head->next;
	}
	head->next = New;
	New->next = NULL;
	
	printf("\nRegistered library account successfully!\n");
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

User *login(UserList *user_all) {
	char enteredname[30];
	char enteredpass[30];
	char password[30];
	User *head;
	head = user_all->list->next;
	
	printf("\nPlease enter a username: ");
	gets(enteredname);
	if(strcmp(enteredname, "librarian") == 0){
		strcpy(password, "librarian");
	}
	else if(1){
		while(head != NULL){
			if(strcmp(head->username, enteredname)==0){
				strcpy(password, head->password);
				break;
			}
			head = head->next;
		}
	}
	else {
		printf("\nUsername does not exist.\n");
		return NULL;
	}
	printf("\nPlease enter a passward: ");
	gets(enteredpass);
	if(strcmp(enteredpass, password) == 0){
		return head;
	}
	else {
		printf("\nWrong password.\n");
	}
	return NULL;
}

int main(){
	UserList *user_all;
	user_all = (UserList *)malloc(sizeof(UserList));
	user_all->list = (User *)malloc(sizeof(User));
	User *head;
	FILE *fp;
	fp = fopen("users.txt", "r");
	if( fp == NULL) {
		printf("\nError, user file does not exist.\n");
		exit(0);
	}
	load_users(fp, user_all);
	int fclose(FILE *fp);
	reg(user_all);
	head = user_all->list->next;
	while(head != NULL)
	{
		printf("\n%s\n%s\n", head->username, head->password);
		head=head->next;
	}
	printf("%s", login(user_all)->username);
}



void removeNewLine(char* string) {

	size_t length = strlen(string);

	if((length > 0) && (string[length-1] == '\n')) {
		string[length-1] ='\0';
	}
	return;
}
