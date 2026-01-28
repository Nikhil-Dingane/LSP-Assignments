#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;
	int (*fp)(int, int) = NULL;

	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("Unable to laod the dynamic library\n");
		perror("");
		return -1;
	}

	printf("Dynamic library succesfully loaded\n");

	fp = dlsym(handle, "Addition");
	if(fp == NULL)
	{
		printf("Unable to get the Addition function pointer");
		return -2;
	}

	printf("Addition: %d\n", fp(10,15));

	fp = dlsym(handle, "Substraction");
	if(fp == NULL)
	{
		printf("Unable to get the Substraction function pointer");
		return -2;
	}

	printf("Substraction: %d\n", fp(10,15));

	return 0;
}
