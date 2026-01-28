#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

int main()
{
	void *handle = NULL;
	void (*fp)() = NULL;

	// This function is used to load the dynmic library
	// in the memory if it is not already in the memory
	// and set its reference count to 1
	// If the dynamic library is already in the memory
	// then its reference count is incremented by 1
	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("Unable to laod the dynamic library\n");
		printf("%s\n",dlerror()); // dlerror return the character array consist the error string occurred while executed dl* functions.
		return -1;
	}

	printf("Dynamic library succesfully loaded\n");

	// Returns the address of the dynamic library function
	// whose name is being passed as the second argument
	fp = dlsym(handle, "display");
	if(fp == NULL)
	{
		printf("Unable to get the display function pointer\n");
		printf("%s\n",dlerror());
		return -2;
	}

	fp();

	// Decrement the the reference of dynamic library by 1
	dlclose(handle);

	return 0;
}
