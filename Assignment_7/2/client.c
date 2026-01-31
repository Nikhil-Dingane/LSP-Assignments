#include <stdio.h>
#include <dlfcn.h>

typedef int (*fpptr)(int, int);

int main()
{
	void *handle1 = NULL, *handle2 = NULL;
	fpptr fp1 = NULL, fp2 = NULL;
	int a = 0, b = 0;

	dlerror();
	handle1 = dlopen("./libaddition.so", RTLD_LAZY);

	if(handle1 == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -1;
	}
	
	dlerror();
	handle2 = dlopen("./libsubstraction.so", RTLD_LAZY);

	if(handle2 == NULL)
	{
		printf("dlopen() failed: %s\n", dlerror());
		return -2;
	}

	dlerror();
	fp1 = dlsym(handle1, "addition");
	if(fp1 == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -3;
	}

	dlerror();
	fp2 = dlsym(handle2, "substraction");
	if(fp2 == NULL)
	{
		printf("dlsym() failed: %s\n", dlerror());
		return -4;
	}

	printf("Enter first value: \n");
	scanf("%d", &a);
	printf("Enter second value: \n");
	scanf("%d", &b);

	printf("Addition is: %d\n", fp1(a, b));
	printf("Substraction is: %d\n", fp2(a, b));

	dlclose(handle1);
	dlclose(handle2);

	return 0;
}
