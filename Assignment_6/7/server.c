#include <stdio.h>
#include "server.h"

int globalVar = 0;

void modifyGlobalVar(int *i)
{
	globalVar = *i;
}

void displayGlobalVar()
{
	printf("%d\n", globalVar);
}

void resetGlobalVar()
{
	globalVar = 0;
}
