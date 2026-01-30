#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

typedef int (*fcnptr)(char *);

int main()
{
	void *handle = NULL;
	char str[1024] = {'\0'};
	fcnptr countUpper, countLower, countDigits;

	printf("Loading shared library...\n");
	dlerror();
	handle = dlopen("./libserver.so", RTLD_NOW);
	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}
	printf("Shared library succesfully loaded\n");

	dlerror();
	countUpper = dlsym(handle, "countUpper");
	if(countUpper == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -1;
	}
	
	dlerror();
	countLower = dlsym(handle, "countLower");
	if(countLower == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -1;
	}
	
	dlerror();
	countDigits = dlsym(handle, "countDigits");
	if(countDigits == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -1;
	}

	printf("Enter the string: \n");
	fflush(stdin);
	scanf("%[^\n]", str);

	printf("Count of upper letters: %d\n", countUpper(str));
	printf("Count of lower letters: %d\n", countLower(str));
	printf("Count of digits: %d\n", countDigits(str));

	dlclose(handle);

	return 0;
}
