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
			}else if((letter == 75) && startPosi >= 20) 
			{

				startPosi -= 20;
				inputted = 1;
				page--;
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
		do
		{
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

//function edit single member information
void editMem(int numStu, int number, FILE* pAcc)
{
		char temp;
		char tmp[50];
		char tmpCode[9];
		strcpy(tmpCode, student[number - 1].studentCode);
		
	do
	{
					if(number <= numStu && number >= 1)
					{
						char tmpName[50];
						strcpy(tmpName, student[number - 1].name);
						
						printf("_");
						char tmpSex[4];
						strcpy(tmpSex, student[number - 1].sex);
								
						int posi  = 1;
						do
						{
							int inputted = 0;
							switch (posi)
							{
								case 1:
									system("cls");
									strcpy(tmp, tmpName);
									while (strlen(tmp) < 28)
									{
										strcat(tmp, " ");
									}
									printf("\n\n\n\n\n\n\n\n");
									printf("\t\t\t.---------------------------------------------------------------\n");
									printf("\t\t\t| *%s|", tmp);
								//	deleteOddSpace(tmpName);
									//printf("_");
									printf("\t%s", tmpSex);
									printf(" ^|v     |");
									printf(" %s\t|\n", tmpCode);
									printf("\t\t\t.---------------------------------------------------------------\n");						
									break;
								case 2:
									system("cls");
									while (strlen(tmpName) < 28)
									{
										strcat(tmpName, " ");
									}
									printf("\n\n\n\n\n\n\n\n");
									printf("\t\t\t.---------------------------------------------------------------\n");
									printf("\t\t\t| %s|", tmpName);
									deleteOddSpace(tmpName);
									printf("\t\t*%s", tmpSex);
									printf(" ^|v     |");
									printf(" %s\t|\n", tmpCode);
									printf("\t\t\t.---------------------------------------------------------------\n");						
									break;
								case 3:
									system("cls");
									while (strlen(tmpName) < 28)
									{
										strcat(tmpName, " ");
									}
									printf("\n\n\n\n\n\n\n\n");
									printf("\t\t\t.---------------------------------------------------------------\n");
									printf("\t\t\t| %s|", tmpName);
									deleteOddSpace(tmpName);
									printf("\t\t %s", tmpSex);
									printf(" ^|v     |");
									printf("*%s\t|\n", tmpCode);	
									printf("\t\t\t.---------------------------------------------------------------\n");					
									break;		
								
							}
							temp = getch();
							
							if( temp == - 32)
							{
								temp = getch();
								if (temp == 77 && posi < 3)
								{
									posi++;
								}
								
								if (temp == 75 && posi >=2)
								{
									posi --;
								
								}
								
								if (temp == 80)
								{
									if (posi == 2)
									{
										if(strcmp(tmpSex, "Nam") == 0)
										{
											strcpy(tmpSex, "Nu");
										} else strcpy(tmpSex, "Nam");
									}
								}
								
								if(temp == 72)
								{
									if (posi == 2)
									{
										if(strcmp(tmpSex, "Nam") == 0)
										{
											strcpy(tmpSex, "Nu");
										} else strcpy(tmpSex, "Nam");
									}
									
								}
							}else if(temp != - 32 )
										{
											if(temp == 32 || (temp >= 48 && temp <= 57) || (temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122))
											{
												if(posi == 1)
												{											
													tmpName[strlen(tmpName) + 1] = '\0';
													tmpName[strlen(tmpName)] = temp;	
												}
												if(posi == 3)
												{
													tmpCode[strlen(tmpCode) + 1] = '\0';
													tmpCode[strlen(tmpCode)] = temp;	
												}
											}	
										}
								
							
							if (temp == 8)
							{
								if (posi == 1)
								{
									tmpName[strlen(tmpName) - 1] = '\0';
								}
								if (posi == 3)
								{
									tmpCode[strlen(tmpCode) - 1] = '\0';
								}
							}
							
						}while(temp != 13 && temp != 27);
						
						if(temp == 13)
						{
							if(checkID(tmpCode, numStu, number - 1) == 2)
							{
								system("cls");
								printf("\n\n\n\n\n\n");
								printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
								printf("\t\t\t\t\t!  The student code has been existed!  !\n");
								printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
								getchar();
							}else if(checkID(tmpCode, numStu, numStu) == 0)
								{
									system("cls");
									printf("\n\n\n\n\n\n");
									printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
									printf("\t\t\t\t\tThe student code is invalid!\n");
									printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
									getchar();
								} else
									{
										
										strcpy(student[number - 1].name, tmpName);
										strcpy(student[number - 1].sex, tmpSex);
										strcpy(student[number - 1].studentCode, tmpCode);
										student[number - 1].course = getCourse((student[number - 1].studentCode));
										sortStuList(numStu);
										writeFile(pAcc, numStu);
										break;
							}
						}
							
					}
					if (temp == 27) break;
	}while(1);
	system("cls");
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
		do
		{
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
				}else if((letter == 75) && startPosi >= 20) 
						{
							startPosi -= 20;
							inputted = 1;
							page--;
						}
						
				number = atoi(tmp);		
				if (letter == 13 && strlen(tmp) >= 1)
				{
					editMem(numStu, number, pAcc);					
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


//function check number
int checkNum(char str[])
{
	for(int i = 0; i <= strlen(str) - 1; i++)
	{
		if(str[i] < 48 || str[i] > 57)
		{
			return 0;
		}
	}
	return 1;
}

//function search student
void searchStudent(int numStu)
{
	char tmp;
	char element[50];
	while(1)
	{
	for (int i = 0; i <= 49; i++)
	{
		element[i] = '\0';
	}
	int i = 0;
	do
	{
		system("cls");
			//printf("\n\n\n\n\n\n\n");
		printf("_______________________________________________________\n");
		printf("| Enter elements you want to find:  %s\n", element);
		printf("_______________________________________________________\n");
		if(strlen(element) > 0)
		{
			for (int j = 0; j <= numStu - 1; j ++)
			{
				if (strstr(student[j].name, element) != '\0')
				{
					char name[50];
					strcpy(name, student[j].name);
					while (strlen(name) < 40)
					{
						strcat(name, " ");
					}
					printf("-------------------------------------------\n");
					printf("| %s|\n", name);
					printf("-------------------------------------------\n");
					//printf("%s\n", student[j].name);
				}else if(strstr(student[j].studentCode, element) != '\0')
					{
						//printf("%s\n", student[j].studentCode);
						char code[9];
						strcpy(code, student[j].studentCode);
						while (strlen(code) < 9)
						{
							strcat(code, " ");
						}
						printf("------------\n");
						printf("| %s|\n", code);
						printf("------------\n");	
									
					}else if(strstr(student[j].sex, element) != '\0')
						{
						
							printf("%s\n", student[j].sex);
							break;
						}else if(checkNum(element))
						{
								if(atoi(element) == student[j].course)
								{
									printf("%d", student[j].course);
									break;	
								}
						}
			}
		}
	
		tmp = getch();
		if(tmp == 32 || (tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
		{
			element[i] = tmp;
			i++;
			upperCase(element);	
		}
		if (tmp == 8)
		{
			i--;
			element[i] = '\0';
		}
		
			
	}while(tmp != 13 && tmp != 27);
	if(tmp == 13 && strlen(element) > 0)
	{
		int found = 0;
		int k = 0;
		system("cls");
		deleteOddSpace(element);
		printf(":-------:--------------------------------------------------:------------:------------:-------:\n");
		printf("|  Ord  |                      Name                        |    Sex     |Student Code| Course|\n");
		printf("|-------:--------------------------------------------------:------------:------------:-------|\n");
		for (int j = 0; j <= numStu - 1; j ++)
		{
			if (checkNum(element))
			{
				if(atoi(element) == student[j].course)
				{
					k++;
					printf("|  %d\t", k);
					printInfo(j);
					found = 1;
					
				}
			
			}else if(strstr(student[j].studentCode, element) != '\0')
				{
						k++;
						printf("|  %d\t", k);
						printInfo(j);
						found = 1;				
				}else if(strstr(student[j].sex, element) != '\0')
					{		
							k++;
							printf("|  %d\t", k);			
							printInfo(j);
							found = 1;
					}else if(strstr(student[j].name, element) != '\0')
						{	
							if(strstr(student[j].name, element) != '\0')
							{
								k++;
								printf("|  %d\t", k);
								printInfo(j);
								found = 1;
							}
						}
		}
		if(!found)
		{
			system("cls");
			printf("\n\n\n\n\n\n");
			printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			printf("\t\t\t\t\t!      Can't find out information!     !\n");
			printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
			getchar();		
		}else
		{
			printf(":-------:--------------------------------------------------:------------:------------:-------:\n");				
			tmp = getch();
		}
	}
	if(tmp == 27) break;
	}
	system("cls");
}


//Function insert members
void InsertMem(FILE* pAcc, int* pNumStu)
{
	char tmp;
	char tmpName[50];
	char tmpCode[10];
	char tmpSex[4];
	do
	{
		int i = 0;
		for(int j = 0; j <= 49; j++)
		{
			tmpName[j] = '\0';
		}
		for(int j = 0; j <= 9; j++)
		{
			tmpCode[j] = '\0';
		}
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter name: ");
			printf("%s\n", tmpName);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter student code:\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Student's sex:  Nu ^|v\n");
			printf("\t\t\t\t\t______________________________________\n");
			tmp = getch();
			if ((tmp == 32) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
			{
				tmpName[i] = tmp;
				i++;
			}
			if(tmp == 8 && i >= 1)
			{
				i--;
				tmpName[i] = '\0';
			}
		} while (tmp != 13 && tmp != 27);
		if(tmp == 27) break;
		deleteOddSpace(tmpName);
		upperCase(tmpName);
		
			i = 0;
			int again = 0;
			do
			{
				do
				{ 
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t______________________________________\n");	
					printf("\t\t\t\t\t| Enter name: %s\n", tmpName);
					printf("\t\t\t\t\t______________________________________\n");
					if(again)
					{
						if(checkID(tmpCode, *pNumStu, *pNumStu) == 0)
						{
							printf("\n\t\t\t\t\tThe student code is not valid!");
							printf("\n\t\t\t\t\t| Enter student code: \n");
							printf("\t\t\t\t\t______________________________________\n");

						}else
						{
							printf("\n\t\t\t\t\tThis student code have been in club already!");
							printf("\n\t\t\t\t\t| Enter student code: \n");
							printf("\t\t\t\t\t______________________________________\n");
						}
						
						for(int j = 0; j <= i - 1; j++)
						{
							tmpCode[j] = '\0';	
						}
						i = 0;
						again = 0;
					}else
						{
							printf("\t\t\t\t\t| Enter student Code: %s\n", tmpCode);
							printf("\t\t\t\t\t______________________________________\n");
						}
					
				//	printf("%s\n", tmpCode);
					printf("\t\t\t\t\t| Student's sex:  Nu ^|v\n");
					printf("\t\t\t\t\t______________________________________\n");
					
					tmp = getch();
					if ((tmp >= 65 && tmp <= 90) || (tmp >= 48 && tmp <= 57))
					{
						tmpCode[i] = tmp;
						i++;
					}
					if(tmp == 8 && i >= 1)
					{
						i--;
						tmpCode[i] = '\0';
					}
				} while (tmp != 13 && tmp != 27);
				
			if(tmp == 27) break;
			again = 0;
			if((checkID(tmpCode, *pNumStu, *pNumStu) == 0) || (checkID(tmpCode, *pNumStu, *pNumStu) == 2) == 1)
			{
				again = 1;		
			}
					
		} while ((checkID(tmpCode, *pNumStu, *pNumStu) == 0) || (checkID(tmpCode, *pNumStu, *pNumStu) == 2));
		if(tmp == 27) break;

		strcpy(tmpSex, "Nu");
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter name: ");
			printf("%s\n", tmpName);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Enter student code: %s\n", tmpCode);
			printf("\t\t\t\t\t______________________________________\n");
			printf("\t\t\t\t\t| Student's sex:  %s ^|v\n", tmpSex);
			printf("\t\t\t\t\t______________________________________\n");
			tmp = getch();
			
			if(tmp == - 32 || tmp == 80 || tmp == 72)
			{
				if(tmp == 80 || tmp == 72)
				if (strcmp(tmpSex, "Nu") == 0)
				{
					strcpy(tmpSex, "Nam");
				}else strcpy(tmpSex, "Nu");
			}
		} while(tmp != 13 && tmp != 27);
		
	
	}while (tmp != 27 && tmp != 13);
	//them cai dk neus maf enter thif moiws copy voiws viet vo tep
	
	if(tmp == 13)
	{
		strcpy(student[*pNumStu].name, tmpName);
		strcpy(student[*pNumStu].studentCode, tmpCode);
		strcpy(student[*pNumStu].sex, tmpSex);
		
	student[*pNumStu].course = getCourse(student[*pNumStu].studentCode);
	
		int j = 0;
		for (int i = 5; i <= strlen(student[*pNumStu].studentCode) - 1; i++)
		{
			student[*pNumStu].pass[j] = student[*pNumStu].studentCode[i];
			j++;
		}
		system("cls");
		printf("\n\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t****************************************\n");
		printf("\t\t\t\t\t*      Add a member successfully!      *\n");
		printf("\t\t\t\t\t****************************************\n");
		getchar();
	(*pNumStu)++;
	sortStuList(*pNumStu);
	
	writeFile(pAcc, *pNumStu);
	}
	system("cls");
		
}

//function change password
void changePass(int numAcc)
{
	int change = 0;
	char starOld[10];
	char starFirstPass[10];
	char starSecondPass[10];
	char oldPass[10];
	char firstPass[10];
	char secondPass[10];

	char tmp;
	do
		{
		for(int i = 0; i<= 9; i++)
		{
			starOld[i] = '\0';
			starFirstPass[i] = '\0';
			starSecondPass[i] = '\0';
			oldPass[i] = '\0';
			firstPass[i] = '\0';
			secondPass[i] = '\0';
		}
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
			int i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starOld[i] = '*';
					oldPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8)
				{
					i--;
					starOld[i] = '\0';
					oldPass[i] = '\0';
				}
					
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;
		
			i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starFirstPass[i] = '*';
					firstPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8)
				{
					i--;
					starFirstPass[i] = '\0';
					firstPass[i] = '\0';
				}
					
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;	
		
			i = 0;
			do
			{
				system("cls");
				printf("\n\n\n\n\n\n");
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter your old password: %s\n", starOld);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password: %s\n", starFirstPass);
				printf("\t\t\t\t\t______________________________________________\n");
				printf("\t\t\t\t\t| Enter new password again: %s\n", starSecondPass);
				printf("\t\t\t\t\t______________________________________________\n");
				
				tmp = getch();
				if((tmp >= 48 && tmp <= 57) || (tmp >= 65 && tmp <= 90) || (tmp >= 97 && tmp <= 122))
				{
					starSecondPass[i] = '*';
					secondPass[i] = tmp;
					i++;
				}
			
				if(tmp == 8)
				{
					i--;
					starSecondPass[i] = '\0';
					secondPass[i] = '\0';
				}
			
			
			}while (tmp != 27 && tmp != 13);
	
			if (tmp == 27) break;
			
		}while (tmp != 13);
	
		if(tmp == 13)
		{
			if(strcmp(oldPass, student[numAcc].pass) == 0)
			{
				if(strcmp(firstPass, secondPass) == 0)
				{
					strcpy(student[numAcc].pass, firstPass);
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t\t****************************************\n");
					printf("\t\t\t\t\t\t*  Change your password successfully!  *\n");
					printf("\t\t\t\t\t\t****************************************\n");
					getchar();
					system("cls");
					change = 1;	
				}else
				{
					system("cls");
					printf("\n\n\n\n\n\n\n\n");
					printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					printf("\t\t\t\t\t!   Enter your new password again!   !\n");
					printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
					getchar();
				}
			}else 
			{
				system("cls");
				printf("\n\n\n\n\n\n\n");
				printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				printf("\t\t\t\t\t!  Your password is not correct!  !\n");
				printf("\t\t\t\t\t!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
				getchar();
			}
		
		}
		
		if(tmp == 27) 
		{
			system("cls");
			break;
		}
	}while(!change);
	printInfo(numAcc);
}


//function cotrol account
void controlAcc(int numAcc, FILE* pAcc, int numStu)
{
	printInfo(numAcc);
	int choice;
	char password[20];
	do
	{
		printf("\n\n\n\n\n\n\n");
		printf("\t\t\t\t\t.--------------------------------.\n");
		printf("\t\t\t\t\t| 1. Edit your information       |\n");
		printf("\t\t\t\t\t| 2. change your password        |\n");
		printf("\t\t\t\t\t| 3. Exit                        |\n");
		printf("\t\t\t\t\t.--------------------------------.\n");
		choice = getChoice(3);
		system("cls");
	//	printInfo(numAcc);
		switch (choice)
		{
			case 1:
			//	editInfo(numAcc, pAcc, numStu);
				editMem(numStu, numAcc + 1, pAcc);
				printInfo(numAcc);
				break;
			case 2:
				changePass(numAcc);
				break;
//				printf("Enter your old password: ");
//				scanf("%s", &password);
//				if (strcmp(password, student[numAcc].pass) == 0)
//				{
//					printf("Enter your new password: ");
//					scanf("%s", &student[numAcc].pass);
//					system("cls");
//					printInfo(numAcc);
//					system("cls");
//					printf("Change your password successfully!\n");	
//					fflush(stdin);
//					getchar();
//					system("cls");
//					printInfo(numAcc);
//					writeFile(pAcc, numStu);
//				} else
//					{
//						int stop = 1;
//						while(strcmp(password, student[numAcc].pass) != 0)
//						{
//							printf("The password is not correct!\n");
//							printf("Press 1 to continue!\n");
//							printf("Press 0 to back!\n");
//							
//							scanf("%d", &stop);
//							system("cls");
//							printInfo(numAcc);
//							if (stop == 0)
//							{
//								break;
//							}
//							printf("Enter password again: ");
//							scanf("%s", &password);
//						}
//						if (stop != 0)
//						
//							printf("Enter your new password: ");
//							scanf("%s", &student[numAcc].pass);
//							system("cls");
//							printInfo(numAcc);	
//							printf("Change your password successfully!\n");	
//							writeFile(pAcc, numStu);
			
//					}
//				break;	
		}
//	system("cls");

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
					searchStudent(*pNumStu);
					break;
				case 3:
					InsertMem(pAcc, pNumStu);
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
							searchStudent(*pNumStu);
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
		getPassword(password, username);
		
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
