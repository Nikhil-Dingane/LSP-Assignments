/***************************************************************

  3) Check File Access Permission
	• Accept file name and mode (read/write/execute).
	• Use access() to check permission for current process.
	• Print “Accessible / Not accessible” with reason.

***************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

#define IN
#define OUT

typedef int BOOL;

#define TRUE 1
#define FALSE 0

BOOL getModeFromStr(IN char* modeStr, OUT int* mode)
{
	*mode = F_OK;

	if(strcmp(modeStr, "read") == 0)
	{
		*mode = *mode | R_OK;
	}
	else if(strcmp(modeStr, "write") == 0)
	{
		*mode = *mode | W_OK;
	}
	else if(strcmp(modeStr, "execute") == 0)
	{
		*mode = *mode | X_OK;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("%s <file path> <mode>\n", argv[0]);
		return -1;
	}

	int mode;

	if(!getModeFromStr(argv[2], &mode))
	{
		printf("Wrong mode: %s\n", argv[2]);
		return -2;
	}

	int iRet = access(argv[1], mode);

	if(iRet == -1)
	{
		if(errno == EACCES)
		{
			printf("File or directory does not have %s permissions\n", argv[2]);
		}
		else
		{
			perror("");
		}
		return -3;
	}

	printf("Fie is Accessible with mode: %s\n",argv[2]);

	return 0;
}
