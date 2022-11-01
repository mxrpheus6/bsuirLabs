#define TRUE 1
#define FALSE 0
int length(char* string)
{
	int i = 0;
	for (i; string[i] != '\0'; i++);
	return i - 1;
}
int isdigit(char* string)
{
	int len = length(string);
	for (int i = 0; i < len; i++)
	{
		if (i == 0 && string[i] == '-')
		{
			continue;
		}
		if (!(string[i] - '0' <= 9 && string[i] - '0' >= 0))
		{
			return FALSE;
		}
	}
	return TRUE;
}
int stringtoint(char* string)
{
	int len = length(string), power = len - 1, result = 0, number, check = 0, j = 0;
	for (int i = 0; i < len; i++)
	{
		if (i == 0 && string[i] == '-')
		{
			check++;
			i++;
		}
		number = (int)string[i] - 48;
		int j;
		if (check == 1)
		{
			j = 1;
		}
		else
		{
			j = 0;
		}
		for (j; j < power; j++)
		{
			number *= 10;
		}
		result += number;
		power--;
	}
	if (check == 1)
	{
		result = -result;
	}
	return result;
}
int compare(char* string1, char* string2)
{
	int len1, len2;
	len1 = length(string1);
	len2 = length(string2);
	if (len1 == len2)
	{
		for (int i = 0; i < len1; i++)
		{
			if (string1[i] != string2[i])
			{
				return FALSE;
			}
		}
	}
	else
	{
		return FALSE;
	}
	return TRUE;
}
int signedrand()
{
	if (rand() % 2 == 0)
	{
		return rand() % 100;
	}
	else
	{
		return -rand() % 100;
	}
}