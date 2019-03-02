////decentralize student
//int decentralizeStu(char username[])
//{
//	if(strcmp(username, "SE130122") == 0 || strcmp(username, "SE130129") == 0 || strcmp(username, "SE130124") == 0)
//	{
//		return 1;
//	}else if(strcmp(username, "SE120113") == 0)
//		{
//			return 2;	
//		}else return 0;
//	
//}
//decentralize student
int decentralizeStu(char username[], char ad1[], char ad2[], char ad3[], char ad4[])
{
	if(strcmp(username, ad1) == 0 || strcmp(username, ad2) == 0 || strcmp(username, ad3) == 0)
	{
		return 1;
	}else if(strcmp(username, ad4) == 0)
		{
			return 2;	
		}else return 0;
	
}
