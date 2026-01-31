#include <stdio.h>
#include <dlfcn.h>

int main()
{
	void *handle = NULL;
	void (*display)(char *) = NULL;
	char str[1024] = {'\0'};

	dlerror();
	handle = dlopen("./libdisplay.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}
	
	dlerror();
	display = dlsym(handle, "display");
	if(display == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -4;
	}

	printf("Enter first value: \n");
	scanf("%[^\n]", str);

	display(str);

	dlclose(handle);

	return 0;
}
