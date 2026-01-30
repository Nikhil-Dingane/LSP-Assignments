#include <stdio.h>
#include "server.h"

int countUpper(char *str)
{
	int cnt = 0;
	for(int i = 0; *(str + i) != '\0'; i++)
	{
		if(*(str + i) >= 'A' && *(str + i) <='Z')
			cnt++;
	}
	return cnt;
}
int countLower(char *str)
{
	int cnt = 0;
	for(int i = 0; *(str + i) != '\0'; i++)
	{
		if(*(str + i) >= 'a' && *(str + i) <= 'z')
			cnt++;
	}
	return cnt;
}
int countDigits(char *str)
{
	int cnt = 0;
	for(int i = 0; *(str + i) != '\0'; i++)
	{
		if(*(str + i) >= '0' && *(str + i) <= '9')
			cnt++;
	}
	return cnt;
}
