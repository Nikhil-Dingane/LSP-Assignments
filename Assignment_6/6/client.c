#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;

	printf("Loading shared library...\n");
	dlerror();
	handle = dlopen("libserver.so", RTLD_NOW);
	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}

	printf("Shared library succesfully loaded\n");

	// Decrement the the reference of dynamic library by 1
	dlclose(handle);

	return 0;
}
