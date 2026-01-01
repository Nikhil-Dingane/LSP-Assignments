/**************************************************************************************

  3 File Counter + Size Report

    Create dir_report.c that recursively calculates:
	• Total number of files
	• Total number of directories
	• Total size of regular files (in bytes)
	• Largest file name + size
	• Count a directory when you enter it.
	• For size: consider only regular files (S_ISREG).
	• Ignore symlink target size (treat symlink as link object only).

    Output:
	Files: 120
	Dirs : 15
	Total Size: 9823412 bytes
	Largest: Marvellous.mp4 (2341123 bytes)

**************************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>

#define PATH_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

int totalNumOfRegFiles = 0;
int totalNumOfDirs = 1;
off_t totalSizeOfRegFiles = 0;
char *largestFileSizeName = NULL;
off_t largestFileSize = 0;

BOOL getReport(char *dirPath)
{
	DIR* directory;

	if((directory = opendir(dirPath)) == NULL)
	{
		perror(dirPath);
		return FALSE;
	}

	struct dirent* dirEnt = NULL;

	while((dirEnt = readdir(directory)) != NULL)
	{
		if((strcmp(dirEnt->d_name, ".") == 0)
		|| (strcmp(dirEnt->d_name, "..") == 0))
			continue;

		if(dirEnt->d_type == DT_REG)
		{
			totalNumOfRegFiles++;
			char filePath[PATH_SIZE] = {'\0'};
			if(dirPath[strlen(dirPath) -1] == '/')
				snprintf(filePath, PATH_SIZE, "%s%s", dirPath, dirEnt->d_name);
			else
				snprintf(filePath, PATH_SIZE, "%s/%s", dirPath, dirEnt->d_name);
			struct stat fileStat;
			if(stat(filePath, &fileStat) == -1)
			{
				perror(filePath);
				continue;
			}

			if(fileStat.st_size > largestFileSize)
			{
				largestFileSize = fileStat.st_size;
				if(largestFileSizeName != NULL)
					free(largestFileSizeName);

				largestFileSizeName = strdup(filePath);
			}

			totalSizeOfRegFiles += fileStat.st_size;
		}
		else if(dirEnt->d_type == DT_DIR)
		{
			totalNumOfDirs++;
			char childDirPath[PATH_SIZE] = {'\0'};
			snprintf(childDirPath, PATH_SIZE, "%s%s", dirPath, dirEnt->d_name);
			getReport(childDirPath);
		}
	}

	closedir(directory);
	return TRUE;
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <dir path>\n", argv[0]);
		return -1;
	}

	getReport(argv[1]);

	printf("Total number of regular files: %d\n", totalNumOfRegFiles);
	printf("Total number of directories: %d\n", totalNumOfDirs);
	printf("Total size of regular files: %ld\n", totalSizeOfRegFiles);
	printf("Largest size file name: %s\n", largestFileSizeName);
	printf("Largest file size: %ld\n", largestFileSize);

	return 0;
}
