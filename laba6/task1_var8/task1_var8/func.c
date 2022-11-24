#include "func.h"

#define TRUE 1
#define FALSE 0

int length(char* string)
{
	int i = 0;
	for (i; string[i] != '\0'; i++);
	return i - 1;
}
int compare_strings(char* string1, char* string2)
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