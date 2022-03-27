#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "book_management.h"
#include "users.h"
#include "utility.h"




int reg(User *user_all) {
	char enteredname[99];
	char enteredpass[99];
	
	User *head;
	head = user_all->next;
	printf("\nPlease enter a username: ");
	gets(enteredname);
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
	printf("\nPlease enter a passward: ");
	gets(enteredpass);
	
	User *New;
	New = (User *)malloc(sizeof(User));
	New->username = (char*)malloc(sizeof(char)*99);
	New->password = (char*)malloc(sizeof(char)*99);
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



char *login(User *user_all) {
	char enteredname[99];
	char enteredpass[99];
	User *head;
	head = user_all->next;
	
	printf("\nPlease enter a username: ");
	gets(enteredname);
	if(strcmp(enteredname, "librarian") == 0){
		printf("\nPlease enter a passward: ");
		gets(enteredpass);
		if(strcmp(enteredpass, "librarian") == 0){
			return "librarian";
		}
		else{
			printf("Wrong password");
			return NULL;
		}
	}
	else{
		while(head != NULL){
			if(strcmp(head->username, enteredname)==0){
				printf("\nPlease enter a passward: ");
				gets(enteredpass);
				if(strcmp(enteredpass, head->password) == 0){
					return head->username;
				}
				else{
					printf("Wrong password.");
					return NULL;
				}
			}
			head = head->next;
		}
		printf("\nUsername does not exist.\n");
		return NULL;
	}
	
	return NULL;
}
