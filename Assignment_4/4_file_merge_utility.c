/********************************************************************

  4. File Merge Utility

    Problem Statement:
	Merge multiple input files into a single output file.

    Input:
	output_file file1 file2 file3 ...

    Output:
	Combined file content in order.

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

BOOL mergeFiles(int argc, char* argv[])
{
	int dstFileFd = -1, srcFileFd = -1;

	if(!openDestinationFileToWrite(&dstFileFd, argv[1]))
		return FALSE;
	
	for(int i = 2; i < argc; i++)
	{
		srcFileFd = open(argv[i], O_RDONLY);
		if(errno == -1)
		{
			perror(argv[i]);
			return FALSE;
		}

		if(!copyData(srcFileFd, dstFileFd))
			return FALSE;

		close(srcFileFd);
	}

	close(dstFileFd);
	return TRUE;
}

int main(int argc, char *argv[])
{
	if(argc < 3)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <output file path> <file1> <file2> <file3> ....\n", argv[0]);
		return -1;
	}

	if(!mergeFiles(argc, argv))
		return -2;

	printf("Data of all files are written to the file %s successfully\n", argv[1]);

	return 0;
}
