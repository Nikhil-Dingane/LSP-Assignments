#include <stdio.h>
#include <dlfcn.h>

int main()
{
	void *handle = NULL;
	int (*mystrlen)(char *) = NULL;
	char str[1024] = {'\0'};

	dlerror();
	handle = dlopen("./libmystrlen.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}
	
	dlerror();
	mystrlen = dlsym(handle, "mystrlen");
	if(mystrlen == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -4;
	}

	printf("Enter first value: \n");
	scanf("%[^\n]", str);

	printf("String length: %d\n", mystrlen(str));

	dlclose(handle);

	return 0;
}
