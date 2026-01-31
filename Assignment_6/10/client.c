#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

#include "server.h"

typedef void (*fcnptr)();

int main()
{
	void *handle = NULL;
	char buffer[1024] = {'\0'};
	fcnptr fp = NULL;

	printf("Enter the library name: \n");
	scanf("%s", buffer);

	printf("Loading shared library...\n");
	dlerror();
	handle = dlopen(buffer, RTLD_NOW);
	if(handle == NULL)
	{
		printf("dlopen(%s) failed: %s\n", buffer, dlerror());
		return -1;
	}
	printf("Shared library succesfully loaded\n");

	memset(buffer, '\0', 1024);
	printf("Enter the function name to search in the library: \n");
	scanf("%s", buffer);
	dlerror();
	fp = dlsym(handle, buffer);
	if(fp == NULL)
	{
		printf("dlsym(%s) failed: %s\n", buffer, dlerror());
		return -2;
	}
	fp();

	dlclose(handle);

	return 0;
}
