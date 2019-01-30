#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char password[10];
	char username[10];
	
	getUsername(username);
	getPassword(password);
	
	puts(username);
	puts(password);
	
	return 0;
}
