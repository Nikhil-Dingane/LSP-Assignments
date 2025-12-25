/*******************************************************************

  4) Delete All Empty Regular Files
	• Accept directory name.
	• Delete files with size = 0 bytes (regular files only).
	• Print names deleted + total deleted count.

*******************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

#define PATH_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

BOOL deleteEmptyFiles(DIR* directory, char* dirPath, int* deletedCount)
{
	struct dirent* dirEntry = NULL;
	struct stat fileStat;

	errno = 0;
	while((dirEntry = readdir(directory)) != NULL)
	{
		char filePath[PATH_SIZE] = {'\0'};

		if(strcmp(dirEntry->d_name, ".") == 0 ||
		   strcmp(dirEntry->d_name, "..") == 0)
			continue;

		snprintf(filePath, PATH_SIZE, "%s/%s", dirPath, dirEntry->d_name);

		if(stat(filePath, &fileStat) == -1)
			continue;

		if(S_ISREG(fileStat.st_mode) && fileStat.st_size == 0)
		{
			if(unlink(filePath) == -1)
			{
				perror("Unable to delete file");
				return FALSE;
			}

			printf("Deleted: %s\n", filePath);
			(*deletedCount)++;
		}
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <directory path>\n", argv[0]);
		return -1;
	}

	DIR* directory = NULL;
	int deletedCount = 0;

	if((directory = opendir(argv[1])) == NULL)
	{
		perror(argv[1]);
		return -2;
	}

	if(!deleteEmptyFiles(directory, argv[1], &deletedCount))
	{
		printf("Failed to delete empty files\n");
	}
	else
	{
		printf("Total empty files deleted: %d\n", deletedCount);
	}

	closedir(directory);

	return 0;
}

