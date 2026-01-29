#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <time.h>

#include "server.h"

int main()
{
	struct timespec t1, t2;
	void *handle = NULL;
	void (*fp)() = NULL;

	// clear old error
	dlerror();

	printf("Loading shared library with RTLD_NOW...\n");
	clock_gettime(CLOCK_MONOTONIC, &t1);
	handle = dlopen("./libserver.so", RTLD_NOW);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s", dlerror());
		return -1;
	}

	clock_gettime(CLOCK_MONOTONIC, &t2);
	printf("Shared library succesfully loaded within %ld nano seconds with RTLD_NOW.\n", (t2.tv_nsec - t1.tv_nsec));

	dlclose(handle);

	printf("Unloaded Shared library...");
	
	printf("Loading shared library with RTLD_LAZY...\n");
	clock_gettime(CLOCK_MONOTONIC, &t1);
	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s", dlerror());
		return -1;
	}

	clock_gettime(CLOCK_MONOTONIC, &t2);
	printf("Shared library succesfully loaded within %ld nano seconds with RTLD_LAZY.\n", (t2.tv_nsec - t1.tv_nsec));

	dlclose(handle);

	printf("Unloaded Shared library...\n");

	printf("RTLD_NOW gets all the function addresses when the library is loaded and RTLD_NOW gets the function addresses when they are used first time.\n");
	printf("That is why RTLD_NOW is slower than RTLD_LAZY\n");

	return 0;
}
