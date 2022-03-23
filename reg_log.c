#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "utility.h"
#include "book_management.h"



int reg(User user) {
	char enteredname[30];
	char enteredpass[30];
	
	User *head, *New;
	head = user.next;
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
	head = user.next;
	while(head->next != NULL){
		head = head->next;
	}
	head->next = New;
	New->next = NULL;
	
	printf("\nRegistered library account successfully!\n");
}



User *login(User user) {
	char enteredname[30];
	char enteredpass[30];
	char password[30];
	User *head;
	head = user.next->next;

	printf("\nPlease enter a username: ");
	scanf("%s", &enteredname);
	while(head != NULL){
		if(strcmp(head->username, enteredname)){
			strcpy(password, head->password);
			break;
		}
		head = head->next;
	}
	if(strcmp(enteredname, "librarian") == 0){
		strcpy(password, "librarian");
	}
	else {
		printf("\nUsername does not exist.\n");
		return NULL;
	}
	printf("\nPlease enter a passward: ");
	scanf("%s", &enteredpass);
	if(strcmp(enteredpass, password) == 0){
		strcpy(password, "librarian");
	}
	else {
		printf("\nWrong password.\n");
	}

	return 0;

}