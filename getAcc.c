
// Get username
void getUsername(char username[])
{
	printf("Enter your username: ");
//	gets(username);
scanf("%s", username);
}

// Get password
#include <conio.h>
void getPassword(char password[])
{
	printf("Enter your password: ");
	char tmp;
	int i = 0;
	do
	{
		tmp = getch();
		if(tmp != 13)
		{
			printf("*");
			password[i] = tmp;
			i++;
		}
	} while (tmp != 13);
	password[i] ='\0';

}
