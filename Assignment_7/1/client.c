#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

int main()
{
	void *handle = NULL;
	int (*fp)(int) = NULL;
	int n = 0;

	printf("Enter number: ");
	scanf("%d", &n);

	dlerror();
	handle = dlopen("./libperfect.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}

	dlerror();
	fp = dlsym(handle, "IsPerfect");

	if(fp == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -2;
	}

	if (fp(n))
		printf("%d is a PERFECT number\n", n);
	else
		printf("%d is NOT a perfect number\n", n);

	return 0;
}
