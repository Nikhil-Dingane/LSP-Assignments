#include<stdio.h>

int mystrlen(char *str)
{
	if(str == NULL)
		return 0;

	int cnt = 0;
	while(*(str + cnt) != '\0')
		cnt++;
	
	if(cnt == 0)
		return 0;
	else
		return (cnt + 1);
}
