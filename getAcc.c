#include <conio.h>
#include"print_logo.h"
#include"print_menu.h"
#include"gotoxy.h"

void getAcc(char username[], char password[])
{
	char star[9];
	for(int i = 0; i <= 8; i++)
	{
		username[i] = '\0';
		password[i] = '\0';
		star[9];
	}
	char tmp;	
	int posi = 1;
	int j = 0;
	int i = 0;
	do
	{
	
		switch(posi)
		{
			case 1: 
				system("cls");
				gotoxy(0,8);
				printFCode();
				printf("\n\n\n");
				printf("%60.0s");
				printfGreen(":--------------------------------------------------------:\n");
				printf("%60.0s");
				printfGreen("|   Enter your username: ");
				printf("%s\n", username);
				printf("%60.0s");
				printfGreen("|                                                        |\n");
				printf("%60.0s");
				printf("|   Enter your password: ");
				printf("%s\n", star);
				printf("%60.0s");
				printfGreen(":--------------------------------------------------------:\n");
				
				gotoxy(117, 24);
				printfGreen("|");
				gotoxy(117, 25);
				printfGreen("|");
				gotoxy(117, 26);
				printfGreen("|");
				break;
			case 2: 
				system("cls");
				gotoxy(0,8);
				printFCode();
				printf("\n\n\n");
				printf("%60.0s");
				printfGreen(":--------------------------------------------------------:\n");
				printf("%60.0s");
				printf("|   Enter your username: ");
				printf("%s\n", username);
				printf("%60.0s");
				printfGreen("|                                                        |\n");
				printf("%60.0s");
				printfGreen("|   Enter your password: ");
				printf("%s\n", star);
				printf("%60.0s");
				printfGreen(":--------------------------------------------------------:\n");
				
				gotoxy(117, 24);
				printfGreen("|");
				gotoxy(117, 25);
				printfGreen("|");
				gotoxy(117, 26);
				printfGreen("|");
				break;
			}
			tmp = getch();
			if(tmp == -32)
			{
				tmp = getch();
				if(tmp == 80 && posi < 2)
				{
					posi++;
				}
				if(tmp == 72 && posi > 1)
				{
					posi--;
				}	
			}else 
				{
					if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
					{
						if(posi == 1 && i <= 7)
						{
							username[i] = tmp;
							i++;
						}
						if(posi == 2 && j <= 7)
						{
							star[j] = '*';
							password[j] = tmp;
							j++;
						}
					}
				}
			if(tmp == 8)
			{
				if(posi == 1 && i >= 1)
				{
					i--;
					username[i] = '\0';
				}
				if(posi == 2 && j >= 1)	
				{
					j--;
					password[j] = '\0';
					star[j] = '\0';	
				}
			}				
	} while(tmp != 13 || i == 0 || j == 0);
		password[j] = '\0';
		star[j] = '\0';
		username[i] = '\0';
}
