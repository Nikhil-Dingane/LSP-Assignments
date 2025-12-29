/********************************************************************

  1. File Copy Utility

    Problem Statement:
	Write a program that copies the contents of one file into another.

    Input:
	Source file name and destination file name as command-line arguments.

    Output:
	Destination file containing an exact copy of source file.
	• Handle file-not-found and permission errors.
	• Destination file should be created if not present.

********************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

#define BLOCK_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

BOOL copyData(int srcFileFd, int dstFileFd)
{
	char buffer[BLOCK_SIZE] = {'\0'};
	int iRet = 0;

	errno = 0;
	while((iRet = read(srcFileFd, buffer, BLOCK_SIZE)) != 0)
	{
		if(errno)
		{
			perror("Unable to read from the source file");
			return FALSE;
		}

		write(dstFileFd, buffer, iRet);

		if(errno)
		{
			perror("Unable to write to the destination file");
			return FALSE;
		}

		memset(buffer, '\0', BLOCK_SIZE);
	}

	return TRUE;
}

BOOL enableFileWritePermissions(char* dstFileName)
{
	struct stat fileStat;

	if(stat(dstFileName, &fileStat) == -1)
	{
		perror(dstFileName);
		return FALSE;
	}

	if(chmod(dstFileName, fileStat.st_mode | S_IWUSR | S_IWGRP | S_IWOTH) == -1)
	{
		perror("Unable to change the mode of destination file");
		return FALSE;
	}

	return TRUE;
}

BOOL openDestinationFileToWrite(int* dstFileFd, char* dstFileName)
{
	*dstFileFd = open(dstFileName, O_WRONLY);
	if(*dstFileFd == -1)
	{
		if((errno == ENOENT) )
		{
			errno = 0;
			if((*dstFileFd = creat(dstFileName, 0777)) == -1)
			{
				perror(dstFileName);
				return FALSE;
			}
		}
		else if(errno == EACCES )
		{
			errno = 0;
			if(!enableFileWritePermissions(dstFileName))
				return FALSE;

			errno = 0;
			if((*dstFileFd = open(dstFileName, O_WRONLY)) == -1)
			{
				perror(dstFileName);
				return FALSE;
			}
		}
		else
		{
			perror(dstFileName);
			return FALSE;
		}
	}

	return TRUE;
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <source file path> <destination file path>\n", argv[0]);
		return -1;
	}

	int srcFileFd = open(argv[1], O_RDONLY);

	if(errno == -1)
	{
		perror(argv[1]);
		return -2;
	}

	int dstFileFd = -1;

	if(!openDestinationFileToWrite(&dstFileFd, argv[2]))
		return -3;

	if(!copyData(srcFileFd, dstFileFd))
		return -4;

	printf("Data from %s file is copied to %s file successfully\n", argv[1], argv[2]);

	return 0;
}
