#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>

#include "perfect.h"

int main()
{

    int n;

    printf("Enter number: ");
    scanf("%d", &n);

    if (IsPerfect(n))
        printf("%d is a PERFECT number\n", n);
    else
        printf("%d is NOT a perfect number\n", n);

    return 0;
}
