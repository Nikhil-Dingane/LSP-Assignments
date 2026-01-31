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
	char funName[10] = {'\0'};
	fcnptr fpArr[5] = {NULL};

	printf("Loading shared library...\n");
	dlerror();
	handle = dlopen("./libserver.so", RTLD_NOW);
	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}
	printf("Shared library succesfully loaded\n");

	for(int i = 1; i <= 5; i++)
	{
		sprintf(funName, "fun%d", i);
		dlerror();
		fpArr[i] = dlsym(handle, funName);
		if(fpArr[i] == NULL)
		{
			printf("dlsym() failed: %s\n", dlerror());
			dlclose(handle);
			return -1;
		}
		printf("Address of function %s is: %ld\n", funName, (long int)fpArr[i]);
		fpArr[i]();
	}

	dlclose(handle);

	return 0;
}
