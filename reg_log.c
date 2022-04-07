#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "book_management.h"
#include "users.h"
#include "utility.h"



//register an account
//returns 0 if the registration is success, or an error code otherwise
int reg(User *user_all) {
	char enteredname[1024];
	char enteredpass[1024];
	
	User *head;
	head = user_all->next;
	printf("\nPlease enter a username: ");
	fgets(enteredname, 1024, stdin);
	removeNewLine(enteredname);
	for(int i=0; enteredname[i]; i++) {
		if(isspace(enteredname[i])) {
			printf("\nSorry, registration unsuccessful, the username should not contain space.\n");
			return 1;
		}
	}
	if(strcmp(enteredname, "librarian")==0){
		printf("\nSorry, registration unsuccessful, the username you entered already exists.\n");
		return 1;
	}
	while(head != NULL){
		if(strcmp(head->username, enteredname)==0 ){
			printf("\nSorry, registration unsuccessful, the username you entered already exists\n");
			return 1;
		}
		head = head->next;
	}
	printf("Please enter a passward: ");
	fgets(enteredpass, 1024, stdin);
	removeNewLine(enteredpass);
	if(strlen(enteredname) == 0||strlen(enteredpass) == 0){
		printf("\nSorry, registration unsuccessful, the username or password is empty\n");
		return 1;
	}
	User *New;
	New = (User *)malloc(sizeof(User));
	New->username = (char*)malloc(sizeof(char)*(strlen(enteredname)+1));
	New->password = (char*)malloc(sizeof(char)*(strlen(enteredpass)+1));
	strcpy(New->username, enteredname);
	strcpy(New->password, enteredpass);
	head = user_all;
	while(head->next != NULL){
		head = head->next;
	}
	head->next = New;
	New->next = NULL;
	
	printf("\nRegistered library account successfully!\n");
	return 0;
}



//login
//returns the username if the login is successful, returns NULL otherwise
char *login(User *user_all) {
	char enteredname[1024];
	char enteredpass[1024];
	User *head;
	head = user_all->next;
	
	printf("\nPlease enter a username: ");
	fgets(enteredname, 1024, stdin);
	removeNewLine(enteredname);
	if(strcmp(enteredname, "librarian") == 0){
		printf("Please enter a passward: ");
		fgets(enteredpass, 1024, stdin);
		removeNewLine(enteredpass);
		if(strcmp(enteredpass, "librarian") == 0){
			return "librarian";
		}
		else{
			printf("\nSorry, wrong password\n");
			return NULL;
		}
	}
	else{
		while(head != NULL){
			if(strcmp(head->username, enteredname)==0){
				printf("Please enter a passward: ");
				fgets(enteredpass, 1024, stdin);
				removeNewLine(enteredpass);
				if(strcmp(enteredpass, head->password) == 0){
					return head->username;
				}
				else{
					printf("\nSorry, wrong password.\n");
					return NULL;
				}
			}
			head = head->next;
		}
		printf("\nSorry, username does not exist.\n");
		return NULL;
	}
	
	return NULL;
}
