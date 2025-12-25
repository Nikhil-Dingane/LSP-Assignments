/*******************************************************************

  3) Move All Files (Dir → Dir)
	• Accept source dir and destination dir.
	• Move all regular files:
	• Use rename() if same filesystem
	• Else copy + delete
	• Print count of moved files.

*******************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define BLOCK_SIZE 1024
#define PATH_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

BOOL copyData(int srcFileFd, int dstFileFd)
{
	char buffer[BLOCK_SIZE] = {'\0'};
	int iRet = 0;

	while((iRet = read(srcFileFd, buffer, BLOCK_SIZE)) > 0)
	{
		if(write(dstFileFd, buffer, iRet) == -1)
		{
			perror("Unable to write to the destination file");
			return FALSE;
		}

		memset(buffer, '\0', BLOCK_SIZE);
	}

	if(iRet == -1)
	{
		perror("Unable to read from the source file");
		return FALSE;
	}

	return TRUE;
}

BOOL copyFilePermissions(int srcFileFd, int dstFileFd)
{
	struct stat fileStat;

	if(fstat(srcFileFd, &fileStat) == -1)
	{
		perror("Unable to get the stat of source file");
		return FALSE;
	}

	if(fchmod(dstFileFd, fileStat.st_mode) == -1)
	{
		perror("Unable to change the mode of destination file");
		return FALSE;
	}

	return TRUE;
}

BOOL copyFile(char* srcFilePath, char* dstFilePath)
{
	int dstFileFd, srcFileFd;

	if((srcFileFd = open(srcFilePath, O_RDONLY)) == -1)
	{
		perror(srcFilePath);
		return FALSE;
	}

	if((dstFileFd = open(dstFilePath, O_CREAT | O_TRUNC | O_WRONLY, 0777)) == -1)
	{
		perror(dstFilePath);
		close(srcFileFd);
		return FALSE;
	}

	if(!copyData(srcFileFd, dstFileFd))
		return FALSE;

	if(!copyFilePermissions(srcFileFd, dstFileFd))
		return FALSE;

	close(srcFileFd);
	close(dstFileFd);

	return TRUE;
}

BOOL isOnSameFileSystem(char* srcDirPath, char* dstDirPath)
{
	struct stat srcDirStat, dstDirStat;

	if(stat(srcDirPath, &srcDirStat) == -1)
	{
		perror(srcDirPath);
		return FALSE;
	}

	if(stat(dstDirPath, &dstDirStat) == -1)
	{
		perror(dstDirPath);
		return FALSE;
	}

	if(srcDirStat.st_dev != dstDirStat.st_dev)
		return FALSE;

	return TRUE;
}

BOOL moveDirFiles(DIR* srcDir, char* srcDirPath, char* dstDirPath, int* movedCount)
{
	struct dirent *dirEntry = NULL;
	struct stat fileStat;

	errno = 0;
	while((dirEntry = readdir(srcDir)) != NULL)
	{
		char srcFilePath[PATH_SIZE] = {'\0'};
		char dstFilePath[PATH_SIZE] = {'\0'};

		if(strcmp(dirEntry->d_name, ".") == 0 ||
		   strcmp(dirEntry->d_name, "..") == 0)
			continue;

		snprintf(srcFilePath, PATH_SIZE, "%s/%s", srcDirPath, dirEntry->d_name);
		snprintf(dstFilePath, PATH_SIZE, "%s/%s", dstDirPath, dirEntry->d_name);

		if(stat(srcFilePath, &fileStat) == -1)
			continue;

		if(!S_ISREG(fileStat.st_mode))
			continue;

		if(rename(srcFilePath, dstFilePath) == 0)
		{
			(*movedCount)++;
			continue;
		}

		if(errno == EXDEV)
		{
			if(!copyFile(srcFilePath, dstFilePath))
				return FALSE;

			if(unlink(srcFilePath) == -1)
			{
				perror("Unable to delete source file");
				return FALSE;
			}

			(*movedCount)++;
		}
		else
		{
			perror("rename failed");
			return FALSE;
		}
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <source directory> <destination directory>\n", argv[0]);
		return -1;
	}

	DIR *srcDir = NULL, *dstDir = NULL;
	int movedCount = 0;

	if((srcDir = opendir(argv[1])) == NULL)
	{
		perror(argv[1]);
		return -4;
	}

	if((dstDir = opendir(argv[2])) == NULL)
	{
		perror(argv[2]);
		closedir(srcDir);
		return -5;
	}

	if(!moveDirFiles(srcDir, argv[1], argv[2], &movedCount))
	{
		printf("Failed to move files\n");
	}
	else
	{
		printf("Total files moved: %d\n", movedCount);
	}

	closedir(srcDir);
	closedir(dstDir);

	return 0;
}
