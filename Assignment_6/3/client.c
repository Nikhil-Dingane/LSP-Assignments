#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "server.h"

typedef double (*fcnptr)(double, double);

int getInput(double *a, double *b)
{
	int input;

	printf("\n");
	printf("1. Addition\n");
	printf("2. Substraction\n");
	printf("3. Multiplication\n");
	printf("4. Division\n");
	printf("5. Exit\n");
	printf("\nEnter your choice: \n");
	scanf("%d", &input);
	if(input >= 5)
		return input;
	printf("Enter first value:\n");
	scanf("%lf", a);
	printf("Enter second value:\n");
	scanf("%lf", b);
	printf("\n");

	return input;
}

void performOperation(void *handle, char *op, double *a, double *b)
{
	fcnptr fp = dlsym(handle, op);

	if(fp == NULL)
	{
		printf("%s", dlerror());
		return;
	}

	printf("%s of %lf and %lf is = %lf\n", op, *a, *b, fp(*a, *b));
}

int main()
{
	void *handle = NULL;
	double (*fp)(double, double) = NULL;
	int run = 1;
	double a = 0, b = 0;

	handle = dlopen("./libserver.so", RTLD_LAZY);

	if(handle == NULL)
	{
		printf("Unable to laod the dynamic library\n");
		printf("%s\n", dlerror());
		return -1;
	}

	printf("Dynamic library succesfully loaded\n");

	while(run)
	{
		switch(getInput(&a, &b))
		{
			case 1:
			{
				performOperation(handle, "Addition", &a, &b);
				break;
			}
			case 2:
			{
				performOperation(handle, "Substraction", &a, &b);
				break;
			}
			case 3:
			{
				performOperation(handle, "Multiplication", &a, &b);
				break;
			}
			case 4:
			{
				performOperation(handle, "Division", &a, &b);
				break;
			}
			case 5:
			{
				run = 0;
				break;
			}
			default:
			{
				printf("Invalid choice\n");
				break;
			}
		}
	}

	dlclose(handle);

	return 0;
}
