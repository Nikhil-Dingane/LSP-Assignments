#include <stdio.h>

void display(char *str)
{
	int cnt = 0;
	while(*(str + cnt) != '\0')
		cnt++;
	
	printf("Input string: %s\n", str);
	printf("Character count: %d\n", (cnt+1));
}
