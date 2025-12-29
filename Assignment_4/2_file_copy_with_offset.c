/************************************************************************

  2. File Copy with Offset

    Problem Statement:
	Copy a file starting from a given byte offset of the source file.

    Input:
	source_file destination_file offset

    Output:
	Partial file copied starting from offset.

************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

#define BLOCK_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

BOOL copyDataFrom(int srcFileFd, int dstFileFd, int offset)
{
	char buffer[BLOCK_SIZE] = {'\0'};
	int iRet = 0;

	errno = 0;

	if(lseek(srcFileFd, offset, (offset > 0) ? SEEK_CUR : SEEK_END) == -1)
	{
		perror("Unable the set the offset in the source file");
		return FALSE;
	}

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
	*dstFileFd = open(dstFileName, O_WRONLY | O_TRUNC);
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
	if(argc < 4)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <source file path> <destination file path> <offset>\n", argv[0]);
		return -1;
	}

	int srcFileFd = open(argv[1], O_RDONLY);

	if(errno == -1)
	{
		perror(argv[1]);
		return -2;
	}

	int dstFileFd = -1;

	int offset = atoi(argv[3]);

	if(!openDestinationFileToWrite(&dstFileFd, argv[2]))
		return -3;

	if(!copyDataFrom(srcFileFd, dstFileFd, offset))
		return -4;

	printf("Data from %s file and offset %d is copied to %s file successfully\n", argv[1], offset, argv[2]);

	return 0;
}
