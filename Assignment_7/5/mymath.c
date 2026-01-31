#include "mymath.h"

double MyPow(double base, int exp)
{
	double result = 1.0;
	int i;

	for (i = 0; i < exp; i++)
	{
		result = result * base;
	}

	return result;
}

double MySqrt(double num)
{
	double guess = num / 2.0;
	int i;

	for (i = 0; i < 25; i++)
	{
		guess = (guess + (num / guess)) / 2.0;
	}

	return guess;
}

int MyAbs(int x)
{
	if (x < 0)
	{
		return -x;
	}

	return x;
}

int MyMax(int a, int b)
{
	if (a > b)
	{
		return a;
	}

	return b;
}

int MyMin(int a, int b)
{
	if (a < b)
	{
		return a;
	}

	return b;
}

int MyFactorial(int n)
{
	int result = 1;
	int i;

	for (i = 1; i <= n; i++)
	{
		result = result * i;
	}

	return result;
}

int MyGCD(int a, int b)
{
	int temp;

	while (b != 0)
	{
		temp = b;
		b = a % b;
		a = temp;
	}

	return a;
}

int MyLCM(int a, int b)
{
	int gcd;

	gcd = MyGCD(a, b);

	return (a * b) / gcd;
}

