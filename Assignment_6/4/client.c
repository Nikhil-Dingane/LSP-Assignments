#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;
	void (*fp)() = NULL;

	// clear old error
	dlerror();

	printf("Loading shared library...\n");
	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s", dlerror());
		return -1;
	}

	printf("Dynamic library succesfully loaded\n");

	// Get address of valid function
	fp = dlsym(handle, "display");
	if(fp == NULL)
		printf("dlsym() failed: %s\n",dlerror());
	else
		fp();

	// Get address of invalid function
	fp = dlsym(handle, "invalid");

	if(fp == NULL)
		printf("dlsym() failed: %s\n", dlerror());
	else
		fp();

	dlclose(handle);

	return 0;
}
