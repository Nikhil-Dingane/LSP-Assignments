#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;
	void (*modifyGlobalVar)(int *);
	void (*displayGlobalVar)();
	void (*resetGlobalVar)();
	int value = 10;

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
	displayGlobalVar = dlsym(handle, "displayGlobalVar");
	if(displayGlobalVar == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -2;
	}
	printf("Shared library global variable initial value: ");
	displayGlobalVar();

	dlerror();
	modifyGlobalVar = dlsym(handle, "modifyGlobalVar");
	if(modifyGlobalVar == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -3;
	}
	modifyGlobalVar(&value);
	printf("Shared library global variable after modification value: ");
	displayGlobalVar();

	dlerror();
	resetGlobalVar = dlsym(handle, "resetGlobalVar");
	if(resetGlobalVar == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -4;
	}
	resetGlobalVar();
	printf("Shared library global variable after reset value: ");
	displayGlobalVar();

	dlclose(handle);

	return 0;
}
