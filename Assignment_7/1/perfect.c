#include <stdio.h>
#include <dlfcn.h>
#include "perfect.h"

int IsPerfect(int No)
{
	void *handle = NULL;
	int (*fp)(int) = NULL;

	if (No <= 0)
		return 0;

	dlerror();
	handle = dlopen("./libhelper.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return 0;
	}

	dlerror();
	fp = dlsym(handle, "SumOfFactors");

	if(fp == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return 0;
	}

	int sum = fp(No);

	return (sum == No);
}
