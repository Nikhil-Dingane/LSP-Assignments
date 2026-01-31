// Note: Intenationally not using the dl functions.
// We have header files of shared libraries
// Hence, we can directly use the function names directly
// instead of using the dl functions to get the function
// addresses.

#include <stdio.h>
#include "mystring.h"
#include "mymath.h"

int main()
{
    int choice;

    char str1[100];
    char str2[100];

    do
    {
        printf("1. String Functions\n");
        printf("2. Math Functions\n");
        printf("0. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("\nEnter first string: ");
            scanf(" %[^\n]", str1);

            printf("Enter second string: ");
            scanf(" %[^\n]", str2);

            printf("\nLength: %d\n", MyStrlen(str1));

            MyStrcat(str1, str2);
            printf("After Concatenation: %s\n", str1);

            printf("Compare Result: %d\n", MyStrcmp(str1, str2));

            MyStrrev(str1);
            printf("After Reverse: %s\n", str1);

            if (MyStrchr(str1, str2[0]) != 0)
            {
                printf("Character '%c' found\n", str2[0]);
            }
            else
            {
                printf("Character '%c' not found\n", str2[0]);
            }
        }

        if (choice == 2)
        {
            int a;
            int b;

            printf("\nEnter two integers: ");
            scanf("%d %d", &a, &b);

            printf("Power: %.2lf\n", MyPow(a, b));
            printf("Square Root: %.2lf\n", MySqrt(a));
            printf("Absolute: %d\n", MyAbs(a));
            printf("Maximum: %d\n", MyMax(a, b));
            printf("Minimum: %d\n", MyMin(a, b));
            printf("Factorial: %d\n", MyFactorial(a));
            printf("GCD: %d\n", MyGCD(a, b));
            printf("LCM: %d\n", MyLCM(a, b));
        }

    }
    while (choice != 0);

    return 0;
}

