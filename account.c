#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "utility.h"
#include "book_management.h"



int reg() {
	char enteredname[30];
	char enteredpass[30];
	int check = 0;
	User *head;
	head = theuser->next;
	printf("\nPlease enter a username: ");
	scanf("%s", &enteredname);
	if(check == 0){
		printf("\nSorry, registration unsuccessful, the username you entered already exists.\n");
	}
	
	else {
		//TODO
	}
	printf("\nPlease enter a passward: ");
	scanf("%s", &enteredpass);
	
	

	
	printf("\nRegistered library account successfully!\n");
}



int login() {
	char enteredname[30];
	char enteredpass[30];
	char password[30];
	User *head;
	head = theuser->next;
	printf("\nPlease enter a username: ");
	scanf("%s", &enteredname);
	if(1){
		//TODO
	}
	else if(strcmp(enteredname, "librarian")){
		strcpy(password, "librarian");
	}
	else {
		//TODO
	}
	printf("\nPlease enter a passward: ");
	scanf("%s", &enteredpass);
	if(strcmp(enteredpass, password)){
		strcpy(password, "librarian");
	}
	else {
		printf("\nWrong password.\n");
	}
	
	printf("\nUsername does not exist.\n");
	
}
