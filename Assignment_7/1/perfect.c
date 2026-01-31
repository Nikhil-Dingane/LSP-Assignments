#include "perfect.h"
#include "helper.h"

int IsPerfect(int No)
{
	if (No <= 0)
		return 0;

	int sum = SumOfFactors(No);

	return (sum == No);
}
