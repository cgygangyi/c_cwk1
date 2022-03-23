#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "utility.h"
#include "book_management.h"



int reg(User user) {
	printf("\nPlease enter a username: ");
	gets();
	printf("\nPlease enter a passward: ");
	printf("\nSorry, registration unsuccessful, the username you entered already exists.\n");
	printf("\nRegistered library account successfully!\n");
}



int login(User user) {
	printf("\nPlease enter a username: ");
	printf("\nPlease enter a passward: ");
	printf("\nUsername does not exist.\n");
	printf("\nWrong password.\n");
}
