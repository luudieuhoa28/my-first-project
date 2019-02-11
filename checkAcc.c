//check account 
int checkAcc(int numStu, char username[], char password)
{
	for (int i = 0; i <= numStu - 1; i++)
	{
		if (username == student[i].studentCode)
		{
			if (password == student[i].pass)
			{
				return 1;
			}else reurn 0;
		}
	}
	return 0;
}
