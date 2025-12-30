/*******************************************************************

  5. Reverse File Content

    Problem Statement:
	Display the contents of a file in reverse order.

    Input:
	File name.

    Output:
	File content printed in reverse.

*******************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>

#define BLOCK_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

int noOfBytesToRead(int* readOffset)
{
	if(*readOffset == 0)
		return 0;
	if(*readOffset < BLOCK_SIZE)
		return *readOffset;
	else
		return BLOCK_SIZE;
}

void moveOffset(int *currOffset, int *moveBy)
{
	*currOffset -= *moveBy;

	if(*currOffset < 0)
		*currOffset = 0;
}

BOOL printReverFileContent(char* fileName)
{
	int fd = -1;
	if((fd = open(fileName, O_RDONLY)) == -1)
	{
		perror(fileName);
		return FALSE;
	}
	
	int readOffset = 0;
	if((readOffset = lseek(fd, 0, SEEK_END)) == -1)
	{
		perror(fileName);
		return FALSE;
	}

	char buffer[1024] = {'\0'};
	int iRet = 0;

	int bytesToRead = noOfBytesToRead(&readOffset);
	moveOffset(&readOffset, &bytesToRead);

	while(bytesToRead != 0 
		&& (iRet = pread(fd, buffer, bytesToRead, readOffset)) > 0)
	{
		for(int i = (iRet - 1); i >= 0; i--)
		{
			putchar(buffer[i]);
		}

		bytesToRead = noOfBytesToRead(&readOffset);
		moveOffset(&readOffset, &iRet);

		memset(buffer, '\0', BLOCK_SIZE);
	}
	
	if(errno)
	{
		perror(fileName);
		return FALSE;
	}

	putchar('\n');
	return TRUE;
}

int  main(int argc, char* argv[])
{
	if(argc < 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file path>\n", argv[0]);
		return -1;
	}

	if(!printReverFileContent(argv[1]))
		return -2;

	return 0;
}
