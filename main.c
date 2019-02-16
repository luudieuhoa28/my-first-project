#include <stdio.h>
#include <stdlib.h>
#include "getAcc.h"
#include <string.h>
#include "decentralize.h"
#include "choice.h"
#include <windows.h>
#include <stdlib.h>
#include "menu.h"
#include <ctype.h>
#include <conio.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Declare the student struct
	struct students 
	{
		char studentCode[9];
		char pass[20];
		int course;
		char sex[4];
		char name[50];
	} student[100];
	
//fuction uppercase name
void upperCase(char str[])
{

	str[0] = toupper(str[0]);
	if (strlen(str) != 1)
	{
		for (int i = 1; i <= strlen(str) - 2; i++)
		{
			if (str[i] == ' ') str[i + 1] = toupper(str[i + 1]);
		}
	}
}

//funtion write updated information on file
void writeFile(FILE* pAcc, int numStu)
{
	pAcc = fopen("account.txt", "w");
	for (int i = 0; i <= numStu - 1; i++)
	{
		fprintf(pAcc, "%s " , student[i].studentCode);
		fprintf(pAcc, "%s ", student[i].pass);
		fprintf(pAcc, "%d ", student[i].course);
		fprintf(pAcc, "%s ", student[i].sex);
		fputs(student[i].name, pAcc);
		if(i != numStu - 1)
		{
			fprintf(pAcc, "\n");
		}
	}
	fclose(pAcc);
}

//function delete odd space
void deleteOddSpace(char str[])
{	
	while (str[0] == ' ') strcpy(&str[0], &str[1]);
	
	for (int i = 0; i <= strlen(str) - 1; i++)
	{
		if(str[i] == ' ' && str[i + 1] ==' ')
		{
			strcpy(&str[i], &str[i + 1]);
			i--;
		}
	}
	
	while(str[strlen(str) - 1] == ' ') strcpy(&str[strlen(str) - 1], &str[strlen(str)]);
}
	
void printInfo(int orderNum)
{
		char name[50];
		strcpy(name, student[orderNum].name);
		while (strlen(name) < 49)
		{
			strcat(name, " ");
		}
		printf("| %s|", name);
		printf("    %s\t|", student[orderNum].sex);
		printf("%10s  |",student[orderNum].studentCode);
		printf("  K%d  |", student[orderNum].course);
	
		printf("\n");
}

//function print information by the table
void printTable(int numStu)
{

	int startPosi = 0;
	char letter;
	int inputted = 1;
	int page = 1;
	do
	{		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int i = 0;
		while(i <= 19 && (i + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", i + startPosi + 1);
			printInfo(i + startPosi);
			i++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!");
		
		
		
		do
		{
			inputted = 0;
			fflush(stdin);
			letter = getch();
		
			if(letter == -32 || letter == 77 || letter == 75)
			{
			if((letter == 77) && startPosi < numStu - 21) 
			{
				startPosi += 20;
				inputted = 1;
				page++;
				//	system("cls");
			}else if((letter == 75) && startPosi >= 20) 
			{

				startPosi -= 20;
				inputted = 1;
				page--;
				//	system("cls");
			}
		}
			fflush(stdin);
		} while(letter != 27 && !inputted);
		system("cls");
	} while(letter != 27);
}

//Function delete members
void deleMem(FILE* pAcc, int* pNumStu, int posi)
{
	for(int i = posi; i <= *pNumStu - 2; i++)
	{
		strcpy(student[i].name, student[i + 1].name);
		strcpy(student[i].pass, student[i + 1].pass);
		strcpy(student[i].sex, student[i + 1].sex);
		strcpy(student[i].studentCode, student[i + 1].studentCode);
		student[i].course = student[i + 1].course;
	}
	(*pNumStu)--;
	 writeFile(pAcc, *pNumStu);
}


//funtion delete member in table directly
void deleteInTable(int numStu, FILE* pAcc)
{
	int number;
	int startPosi = 0;
	char tmp[5];
	char letter;
	int inputted = 0 ;
	int page = 1;
	for(int i = 0; i <= 3; i++)
	{
		tmp[i] = '\0';
	}
	int i = 0;
	
	do
	{	
		if(letter == 13)
		{
			if(strlen(tmp) >= 1)
			{
				int length = strlen(tmp);
				for (int k = 0; k <= length - 1; k++)
				{
					tmp[k] = '\0';
				}
			}
			i = 0;
		}
	//	printf("i = %d", i);
		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int j = 0;
		while(j <= 19 && (j + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", j + startPosi + 1);
			printInfo(j + startPosi);
			j++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!\n");
		printf("\n");
		
		printf("Enter oder number you want to delete: ");
//		printf("sdhksjds %s", tmp);
		do
		{
		//	printf("%s\n", tmp);
			if(inputted)
			{
				printf("%s", tmp);
			}
			inputted = 0;
			
			fflush(stdin);
			letter = getch();
			if(letter >= 48 && letter <= 57)
			{
				printf("%c", letter);
				tmp[i] = letter;
				i++;				
			}else if(letter == - 32 || letter == 77 || letter == 75 || letter == 13 || letter == 8)
			{
				if((letter == 77) && startPosi < numStu - 21) 
				{
					startPosi += 20;
					inputted = 1;
					page++;
					//	system("cls");
				}else if((letter == 75) && startPosi >= 20) 
						{
							startPosi -= 20;
							inputted = 1;
							page--;
				//	system("cls");
						}
				if (letter == 13 && strlen(tmp) >= 1)
				{
					number =  atoi(tmp);	
					if(number <= numStu && number >= 1)
					{
							
						char temp;
						int yes = 1;
						tmp[i] = '\0';
						system("cls");
						printf("\n");
						printf("\n");
						printf("\n");
						printf("                           ___________________________________________________________________________\n");
						printf("                           |                                                                         |\n");
						printf("                           |                  You really want to delete this member?                 |\n");
						printf("                           |                _______                                                  |\n");
						printf("                           |________________|_Yes_|_________________________No_______________________|\n");
						do
						{
						
							temp = getch();
							if(temp == - 32 || temp == 77 || temp == 75)
							{
								if(temp == 77)
								{
									yes = 0;
									system("cls");
									printf("\n");
									printf("\n");
									printf("\n");
									printf("                           ___________________________________________________________________________\n");
									printf("                           |                                                                         |\n");
									printf("                           |                  You really want to delete this member?                 |\n");
									printf("                           |                                             ______                      |\n");
									printf("                           |_________________Yes_________________________|_No_|______________________|\n");
								}
								if(temp == 75)
								{
									yes = 1;
									system("cls");
									printf("\n");
									printf("\n");
									printf("\n");
									printf("                           ___________________________________________________________________________\n");
									printf("                           |                                                                         |\n");
									printf("                           |                  You really want to delete this member?                 |\n");
									printf("                           |                _______                                                  |\n");
									printf("                           |________________|_Yes_|_________________________No_______________________|\n");
								}
							}
						}while(temp != 13);
						if(yes)
						{
							deleMem(pAcc, &numStu, number - 1);
						}
					}
				}
				if (letter == 8 && i > 0)
				{
					tmp[i - 1] = '\0';
					i--;
					inputted = 1;
				}		
			}
	
			
			fflush(stdin);
		} while(letter != 27 && !inputted && letter != 13);

		
		system("cls");
	} while(letter != 27);
}


//function edit information in table
void editInTable(int numStu, FILE* pAcc)
{
		int number;
	int startPosi = 0;
	char tmp[5];
	char letter;
	int inputted = 0 ;
	int page = 1;
	for(int i = 0; i <= 3; i++)
	{
		tmp[i] = '\0';
	}
	int i = 0;
	
	do
	{	
		if(letter == 13)
		{
			if(strlen(tmp) >= 1)
			{
				int length = strlen(tmp);
				for (int k = 0; k <= length - 1; k++)
				{
					tmp[k] = '\0';
				}
			}
			i = 0;
		}
	//	printf("i = %d", i);
		
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		int j = 0;
		while(j <= 19 && (j + startPosi) <= numStu - 1)
		{
			printf("|  %d\t", j + startPosi + 1);
			printInfo(j + startPosi);
			j++;
		}
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("                                            <%d>\n", page);
		printf("press [esc] to exit!\n");
		printf("\n");
		
		printf("Enter oder number you want to edit: ");
//		printf("sdhksjds %s", tmp);
		do
		{
		//	printf("%s\n", tmp);
			if(inputted)
			{
				printf("%s", tmp);
			}
			inputted = 0;
			
			fflush(stdin);
			letter = getch();
			if(letter >= 48 && letter <= 57)
			{
				printf("%c", letter);
				tmp[i] = letter;
				i++;				
			}else if(letter == - 32 || letter == 77 || letter == 75 || letter == 13 || letter == 8)
			{
				if((letter == 77) && startPosi < numStu - 21) 
				{
					startPosi += 20;
					inputted = 1;
					page++;
					//	system("cls");
				}else if((letter == 75) && startPosi >= 20) 
						{
							startPosi -= 20;
							inputted = 1;
							page--;
				//	system("cls");
						}
				if (letter == 13 && strlen(tmp) >= 1)
				{
					system("cls");
					number = atoi(tmp);
					if(number <= numStu && number >= 1)
					{
						printInfo(number - 1);
						editInfo(number - 1, pAcc, numStu);
					}
					
				}
				if (letter == 8 && i > 0)
				{
					tmp[i - 1] = '\0';
					i--;
					inputted = 1;
				}		
			}
	
			
			fflush(stdin);
		} while(letter != 27 && !inputted && letter != 13);

		
		system("cls");
	} while(letter != 27);
}	


//function check ID
int checkID(char str[], int numStu, int numAcc)
{
	if(strlen(str) == 8)
	{
		if((str[0] == 'I' && str[1] == 'A') || (str[0] == 'S' && str[1] == 'E'))
		{
			for(int i = 2; i < 8; i++)
			{
				if(str[i] < '0' || str[i] > '9') return 0;
			}
		}else return 0;
	}else return 0;
	
	for (int i = 0; i <= numStu - 1; i++)
	{
		if (i != numAcc)
		{
			if (strcmp(str, student[i].studentCode) == 0)
			{
				return 2;
			}	
		}
	}
	return 1;
}

//Function search for student's information
void searStu(int numStu)
{

	int choice;
	do
	{
		printf("1. Search by name\n");
		printf("2. Search by student code\n");
		printf("3. Search by student's' course\n");
		printf("4. Search by sex\n");
		printf("5. Exit\n");
		
		char name[50];
		char stuCode[10];
		char sex[4];
		int course, numFormat;
		char endChar;
		int haveFound = 0;
		int count;
		choice = getChoice(5);
		system("cls");
		switch (choice)
		{
			case 1:
				printf("Enter name you want to find out: ");
				gets(name);
				deleteOddSpace(name);
				upperCase(name);
				
				count = 1;
				for(int i = 0; i <= numStu - 1; i++)
				{
					if(strstr(student[i].name, name) != '\0')
					{
						printf("|  %d\t ", count);
						printInfo(i);
						haveFound = 1;
						count++;
					}
				}
				if (haveFound == 0) printf("Can't find out!");
				fflush(stdin);
				getchar();
				system("cls");
				break;
			case 2:
				printf("Enter student code you want to find out: ");
				do
				{
					gets(stuCode);
					if(checkID(stuCode, numStu, numStu) == 0)
					{
						printf("Input again: ");
						fflush(stdin);
					}
				}while(checkID(stuCode, numStu, numStu) == 0);
				
				count = 1;
				for(int i = 0; i <= numStu - 1; i++)
				{
					if (strcmp(stuCode, student[i].studentCode) == 0)
					{
						printf("|  %d\t", count);
						printInfo(i);
						count++;
					}
				}
				if(checkID(stuCode, numStu, numStu) != 2)
				{
					printf("Can't find out!");
				}
				fflush(stdin);
				getchar();
				system("cls");
				break;	
			case 3:
				printf("Enter the course you want to find out: ");
				do
				{
					numFormat = scanf("%d%c", &course, &endChar);
		
					if (numFormat != 2 || endChar != '\n' || course < 1)
					{
						printf("Input again: ");
						fflush(stdin);
					}
				} while(numFormat != 2 || endChar != '\n' || course < 1);
				
				count = 1;
				for (int i = 0; i <= numStu - 1; i++)
				{
					if(course == student[i].course)
					{
						printf("|  %d\t", count);
						printInfo(i);
						haveFound = 1;
						count++;
					}
				}
				
				if(haveFound == 0) printf("Can't find out!");
				fflush(stdin);
				getchar();
				system("cls");
				break;
			case 4:
				printf("Enter student's sex you want to find out: ");
				do
				{
					scanf("%s", sex);
					upperCase(sex);
					if(strcmp(sex, "Nam") != 0 && strcmp(sex, "Nu") != 0)
					{
						printf("input again: ");
						fflush(stdin);
					}
				} while(strcmp(sex, "Nam") != 0 && strcmp(sex, "Nu") != 0);
				count = 1;
				for(int i = 0; i <= numStu - 1; i++)
				{
					if(strcmp(sex, student[i].sex) == 0) 
					{
						printf("|  %d\t", count);
						printInfo(i);
						count++;
					}
				}
				fflush(stdin);
				getchar();
				system("cls");
				break;
			case 5:
				break;			
		}
	} while(choice != 5);
}

void searchStudent(int numStu)
{
	
}

//delete space 
void deteSpa(int numStu)
{	
	for (int i = 0; i <= numStu - 1; i++)
	{
		for(int j = 0; j <= numStu - 2; j++)
		{
			student[i].name[j] = student[i].name[j + 1];
		}
		
		if(i != numStu - 1)
		{
			student[i].name[strlen(student[i].name) - 1] = '\0';
		} else student[i].name[strlen(student[i].name)]= '\0';	
	}
}

//function read student information
void getInfo(FILE* pAcc, int* pNumStu)
{
	*pNumStu = 0;
	while (!feof(pAcc))
	{
		fscanf(pAcc, "%s", &student[*pNumStu].studentCode);
		fflush(stdin);
		
		fscanf(pAcc, "%s", &student[*pNumStu].pass);
		
		fscanf(pAcc, "%d", &student[*pNumStu].course);
		
		fscanf(pAcc, "%s", &student[*pNumStu].sex);

		fgets(student[*pNumStu].name, 50, pAcc);			
		deleteOddSpace(student[*pNumStu].name);
		
		printf("\n");
		(*pNumStu)++;
	}
		for(int i = 0; i <= *pNumStu - 1; i++)
		{
			if(i != (*pNumStu) - 1)
			{
				student[i].name[strlen(student[i].name) - 1] = '\0';			
			}else student[i].name[strlen(student[i].name)] = '\0';
		}
//	deteSpa(*pNumStu);

}

//function check account
int checkAcc(int numStu, char username[], char password[], int* pNumAcc)
{
	for (int i = 0; i <= numStu - 1; i++)
	{
		if (strcmp(username, student[i].studentCode) == 0)
		{		
			if (strcmp(password, student[i].pass) == 0)
			{
				*pNumAcc = i;//to get position of user	
				return 1;
			}else return 0;
		}
	}
	return 0;
}

//function cut string to get single word
void cutWord(char substring[], char sourceString[])
{
	char spa[2] = " ";
	if (strstr(sourceString, spa) == '\0')
	{
		strcpy(substring, sourceString);
	}else 
		{
			for (int i = strlen(sourceString) - 1; i >= 0; i--)
			{
				if(sourceString[i] == ' ')
				{		
					int j = 0;
					for (int k = i + 1; k <= strlen(sourceString); k++)
					{
						substring[j] = sourceString[k];
						j++;						
					}
					sourceString[i] = '\0';
					break;
				}
			}
		}

}	

//Function compare name
int compareString(char name1[], char name2[])
{
	char substring1[8];
	char substring2[8];
	if (strcmp(name1, name2) == 0) return 0;
	while (name1 != '\0' && name2 != '\0')
	{
		cutWord(substring1, name1);
		cutWord(substring2, name2);
		if (strcmp(substring1, substring2) > 0) return 1;
		else if(strcmp(substring1, substring2) < 0) return (- 1);
	}
	return 0;	
}

//function swap student position
void swap(int firstPosi, int secondPosi)
{
	//swap student code
	char tmpStuCode[9];
	strcpy(tmpStuCode, student[firstPosi].studentCode);
	strcpy(student[firstPosi].studentCode, student[secondPosi].studentCode);
	strcpy(student[secondPosi].studentCode, tmpStuCode);
	
	//swap password
	char tmpPass[4];
	strcpy(tmpPass, student[firstPosi].pass);
	strcpy(student[firstPosi].pass, student[secondPosi].pass);
	strcpy(student[secondPosi].pass, tmpPass);
	
	//swap sex
	char tmpSex[4];	
	strcpy(tmpSex, student[firstPosi].sex);
	strcpy(student[firstPosi].sex, student[secondPosi].sex);
	strcpy(student[secondPosi].sex, tmpSex);
	
	//swap name
	char tmpName[50];
	strcpy(tmpName, student[firstPosi].name);
	strcpy(student[firstPosi].name, student[secondPosi].name);
	strcpy(student[secondPosi].name, tmpName);
	
	//swap course
	int tmpCourse = student[firstPosi].course;
	student[firstPosi].course = student[secondPosi].course;
	student[secondPosi].course = tmpCourse;
	
}

//Sort student list
void sortStuList(int numStu)
{
	char tmpName1[50];
	char tmpName2[50];
	for (int i = 0; i <= numStu - 1; i++)
	{
		for (int j = 0; j <= numStu - 2 - i; j++)
		{
			if (student[j].course > student[j + 1].course)
			{
				swap(j, j + 1);
			} else if (student[j].course == student[j + 1].course)
					{
						strcpy(tmpName1, student[j].name);
						strcpy(tmpName2, student[j + 1].name);
						if (compareString(tmpName1, tmpName2) > 0)
						{
							swap(j, j + 1);
						}
					}
		}
	}
}


//Function get course
int getCourse(char studentCode[])
{
	char course[3];
	int j = 0;
	for (int i = 2; i <= 3; i++)
	{
		course[j] = studentCode[i];
		j++;
	}
	return atoi(course);
}

//Function insert members
void InsertMem(FILE* pAcc, int* pNumStu)
{
	printf("Enter name: ");
		gets(student[*pNumStu].name);
		student[*pNumStu].name[strlen(student[*pNumStu].name)] = '\0';
		deleteOddSpace(student[*pNumStu].name);
		upperCase(student[*pNumStu].name);
	
		printf("Enter student code: ");
			do
			{
				scanf("%s", &student[*pNumStu].studentCode);
				if ((checkID(student[*pNumStu].studentCode, *pNumStu, *pNumStu) == 0) || (checkID(student[*pNumStu].studentCode, *pNumStu, *pNumStu) == 2))
				{
					printf("Enter again: ");
				}
			} while ((checkID(student[*pNumStu].studentCode, *pNumStu, *pNumStu) == 0) || (checkID(student[*pNumStu].studentCode, *pNumStu, *pNumStu) == 2));
	
//	printf("Enter student course: ");
//			scanf("%d", &student[*pNumStu].course);
	
		student[*pNumStu].course = getCourse(student[*pNumStu].studentCode);
		
		printf("Enter student sex: ");
		scanf("%s", &student[*pNumStu].sex);
		printf("dhksjdh");
		upperCase(student[*pNumStu].sex);
		fflush(stdin);
	
		printf("dkdsj");	
		int j = 0;
		for (int i = 5; i <= strlen(student[*pNumStu].studentCode) - 1; i++)
		{
			printf("kjdjdskjdlks");
			student[*pNumStu].pass[j] = student[*pNumStu].studentCode[i];
			j++;
		}
	(*pNumStu)++;
	sortStuList(*pNumStu);
	//nho them lenh sap xep ngay day
	printf(".\n");

	printf("..\n");
	
	writeFile(pAcc, *pNumStu);
		
}




//Function edit student information
void editInfo(int numAcc, FILE* pAcc, int numStu)
{
	int choice;
	int numFormat;
	char endChar;
	do 
	{
	//	printInfo(numAcc);
		printf("1. Edit name\n");
		printf("2. Edit course\n");
		printf("3. Edit sex\n");
		printf("4. Edit student code\n");
		printf("5. Exit\n");
		choice =  getChoice(5);
		system("cls");
		printInfo(numAcc);
		switch (choice)
		{
			case 1:
				printf("Enter new name: ");
				gets(student[numAcc].name);
				student[numAcc].name[strlen(student[numAcc].name)] = '\0';
				deleteOddSpace(student[numAcc].name);
				upperCase(student[numAcc].name);
				system("cls");
				printf("Edit successfully!\n");
				printInfo(numAcc);
				sortStuList(numStu);
				writeFile(pAcc, numStu);
				break;
			case 2:
				printf("Enter new course: ");
			//	scanf("%d", &student[numAcc].course);
				do
				{
					numFormat = scanf("%d%c", &student[numAcc].course, &endChar);
		
					if (numFormat != 2 || endChar != '\n' || student[numAcc].course < 1)
					{
						printf("Input again: ");
						fflush(stdin);
					}
				} while(numFormat != 2 || endChar != '\n' || student[numAcc].course < 1);
				system("cls");
				printf("Edit successfully!\n");
				printInfo(numAcc);
				writeFile(pAcc, numStu);
				break;
			case 3:
				printf("Enter new sex: ");
				do
				{
					gets(student[numAcc].sex);
					upperCase(student[numAcc].sex);
					if(strcmp(student[numAcc].sex, "Nam") != 0 && strcmp(student[numAcc].sex, "Nu") != 0)
					{
						printf("input again: ");
						fflush(stdin);
					}
				} while(strcmp(student[numAcc].sex, "Nam") != 0 && strcmp(student[numAcc].sex, "Nu") != 0);
				system("cls");
				printf("Edit successfully!\n");
				printInfo(numAcc);
				writeFile(pAcc, numStu);
				break;
			case 4:
				printf("Enter new student code: ");
				char tmpStuCode[20];
				do
				{
					int stop;
					scanf("%s", &tmpStuCode);
					if ((checkID(tmpStuCode, numStu, numAcc) == 0) || (checkID(tmpStuCode, numStu, numAcc) == 2))
					{
						if(checkID(tmpStuCode, numStu, numAcc) == 0) 
						{
							printf("this ID is invalid!\n");
						} else printf("This ID has been in club!\n");
						printf("Press 1 to continue!\n");
						printf("Press 0 to back!\n");
							
						scanf("%d", &stop);
						system("cls");
						printInfo(numAcc);
						if (stop == 0)
						{
							break;
						}
						printf("Enter ID again: ");
					} else strcpy(student[numAcc].studentCode, tmpStuCode);
				} while ((checkID(tmpStuCode, numStu, numAcc) == 0) || (checkID(tmpStuCode, numStu, numAcc) == 2));
				system("cls");
				if ((checkID(tmpStuCode, numStu, numAcc) != 0) && (checkID(tmpStuCode, numStu, numAcc) != 2))
				{
					printf("Edit successfully!\n");
					student[numAcc].course = getCourse(student[numAcc].studentCode);// get student course from ID
					writeFile(pAcc, numStu);
				}
				printInfo(numAcc);
				break;
			case 5:
				break;		
		}
	} while (choice != 5);
//	writeFile(pAcc, numStu);
}

//function cotrol account
void controlAcc(int numAcc, FILE* pAcc, int numStu)
{
	printInfo(numAcc);
	int choice;
	char password[20];
	do
	{
		printf("1. Edit your information\n");
		printf("2. change your password\n");
		printf("3. Exit\n");
		choice = getChoice(3);
		system("cls");
		printInfo(numAcc);
		switch (choice)
		{
			case 1:
				editInfo(numAcc, pAcc, numStu);
				break;
			case 2:
				printf("Enter your old password: ");
				scanf("%s", &password);
				if (strcmp(password, student[numAcc].pass) == 0)
				{
					printf("Enter your new password: ");
					scanf("%s", &student[numAcc].pass);
					system("cls");
					printInfo(numAcc);
					printf("Change your password successfully!\n");	
					writeFile(pAcc, numStu);
				} else
					{
						int stop = 1;
						while(strcmp(password, student[numAcc].pass) != 0)
						{
							printf("The password is not correct!\n");
							printf("Press 1 to continue!\n");
							printf("Press 0 to back!\n");
							
							scanf("%d", &stop);
							system("cls");
							printInfo(numAcc);
							if (stop == 0)
							{
								break;
							}
							printf("Enter password again: ");
							scanf("%s", &password);
						}
						if (stop != 0)
						{
							printf("Enter your new password: ");
							scanf("%s", &student[numAcc].pass);
							system("cls");
							printInfo(numAcc);	
							printf("Change your password successfully!\n");	
							writeFile(pAcc, numStu);
						}
					}
				break;	
		}
		system("cls");

	}while (choice != 3);
	system("cls");
}

void member(int* pNumStu, char username[], FILE* pAcc, int numAcc)
{
	system("cls");
	int posi;// position is deleted;
	
	int choice;
	if(decentralizeStu(username) == 1)
	{
		do
		{
			printSpeMenu();	
			choice = getChoice(7);
			system("cls");
			switch (choice)
			{
				case 1: 
					printTable(*pNumStu);
					break;
				case 2:
					searStu(*pNumStu);
					break;
				case 3:
					InsertMem(pAcc, pNumStu);
					system("cls");
					printf("Add a member successfully!\n");
					break;
				case 4:
					deleteInTable(*pNumStu, pAcc);
					break;
				case 5:
					editInTable(*pNumStu, pAcc);
					break;
				case 6:
					controlAcc(numAcc, pAcc, *pNumStu);
					break;
				case 7:
					break;									
			}
	
		} while(choice != 7);
						
	}else
		{
			system("cls");
			do
				{
					printNorMenu();
					choice = getChoice(4);
					system("cls");
					switch (choice)
					{
						case 1: 
							printTable(*pNumStu);
							break;
						case 2:
							searStu(*pNumStu);
							break;
						case 3:
							controlAcc(numAcc, pAcc, *pNumStu);	
							break;
					}
				} while(choice != 4);
		}
}

int main(int argc, char *argv[]) {
	char username[9];
	char password[20];
	char letter;
	
	int numAcc;// position to get user account	

	//read student information
	FILE* pAcc;
	
	pAcc = fopen("account.txt", "r");
	
	int numStu;

	getInfo(pAcc, &numStu);
	fclose(pAcc);
		
	//check account and print menu
	do{
		// Get account
		fflush(stdin);
		getUsername(username);
		getPassword(password);
		
		printf("%d", checkAcc(numStu, username, password, &numAcc));
		if(checkAcc(numStu, username, password, &numAcc))
		{
			system("cls");
			int choice;
			//lay tu day
			do
			{
				printMainMenu();
				choice = getChoice(5);
				switch (choice)
				{
					case 1:
						member(&numStu, username, pAcc,numAcc);
						break;
				}
				system("cls");
			}while (choice != 5);
		}else 
			{
			//	system("cls");
				
				printf("Account does not exist!\n");		
			}
		//toi day	
	}while (!checkAcc(numStu, username, password, &numAcc));
	

	return 0;
}
