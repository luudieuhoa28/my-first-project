#include <conio.h>

// Get username
void getUsername(char username[])
{

	char tmp;
	int i = 0;
	for(int i = 0; i <= 8; i++)
	{
		username[i] = '\0';
	}
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("                    _____________________________________________________\n");
		printf("                    |Enter your username: %s\n", username);
		printf("                    _____________________________________________________\n");
		printf("                    |Enter your password: \n");
		printf("                    _____________________________________________________\n");
	
		tmp = getch();
		if(tmp != 13 && tmp != 8)
		{
			username[i] = tmp;
			i++;
		}else if (tmp == 8)
			{
				i--;
				username[i] = '\0';
						
			}
		
	} while (tmp != 13);
	username[i] = '\0';

}

// Get password
void getPassword(char password[], char username[])
{
	char tmp;
	char star[10];
	for(int i = 0; i <= 9; i++)
	{
		star[i] = '\0';
	}
	int i = 0;
	do
	{
		system("cls");
		printf("\n\n\n\n");
		printf("                    _____________________________________________________\n");
		printf("                    |Enter your username: %s\n", username);
		printf("                    _____________________________________________________\n");
		printf("                    |Enter your password: %s\n", star);
		printf("                    _____________________________________________________\n");
	
		tmp = getch();
		if(tmp != 13 && tmp != 8)
		{
			star[i] = '*';
			password[i] = tmp;
			i++;
		}else if (tmp == 8)
			{
				i--;
				password[i] = '\0';
				star[i] = '\0';
						
			}
		
	} while (tmp != 13);
	password[i] = '\0';
	star[i] = '\0';

}
