#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "utility.h"
#include "book_management.h"



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
		return NULL;
	}

}
