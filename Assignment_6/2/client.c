#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;
	void (*fp)() = NULL;

	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("Unable to laod the dynamic library\n");
		printf("%s\n",dlerror());
		return -1;
	}

	printf("Dynamic library succesfully loaded\n");

	fp = dlsym(handle, "display");
	if(fp == NULL)
	{
		printf("Unable to get the display function pointer\n");
		printf("%s\n",dlerror());
		return -2;
	}

	fp();

	dlclose(handle);

	return 0;
}
