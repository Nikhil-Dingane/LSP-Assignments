/******************************************************************************************

  2 Recursive Directory Traversal

	Write tree_clone.c which prints a directory as a tree, like:
	root/
	  a.txt
	  src/
	    Ganesh.c

	• Indentation based on recursion depth
	• Print type markers:
	• [D] directory
	• [F] regular file
	• [L] symbolic link
	• Use lstat() to detect symbolic links.
	• Do not follow symlink directories (avoid loops).

******************************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>

#define PATH_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

char* getDeviceTypeMarker(unsigned char type)
{
	switch (type)
	{
		case DT_BLK:  return "[BD]";
		case DT_CHR:  return "[CD]";
		case DT_DIR:  return "[D]";
		case DT_FIFO: return "[F/P]";
		case DT_LNK:  return "[L]";
		case DT_REG:  return "[F]";
		case DT_SOCK: return "[S]";
		default:      return "[?]";
	}
}

BOOL treeList(char* dirPath, int depth)
{
	DIR* directory = opendir(dirPath);

	if(directory == NULL)
	{
		perror(dirPath);
		return FALSE;
	}

	struct dirent* dirEntry = NULL;
	char *dirName;
	char tempPath[PATH_MAX];

	strcpy(tempPath, dirPath);

	int len = strlen(tempPath);
	if (len > 0 && tempPath[len - 1] == '/')
	{
		tempPath[len - 1] = '\0';
	}

	dirName = strrchr(tempPath, '/');
	if (dirName)
		dirName++;
	else
		dirName = tempPath;

	for(int i = 0; i < (depth * 2); i++)
		putchar(' ');

	printf("[D] %s/\n", dirName);

	while((dirEntry = readdir(directory)) != NULL)
	{
		if((strcmp(dirEntry->d_name, ".") == 0)
		|| (strcmp(dirEntry->d_name, "..") == 0))
			continue;

		if(dirEntry->d_type == DT_DIR)
		{
			char childDirPath[PATH_SIZE] = {'\0'};
			snprintf(childDirPath, PATH_SIZE, "%s%s", dirPath, dirEntry->d_name);
			treeList(childDirPath, depth + 1);
		}
		else if(dirEntry->d_type == DT_LNK)
		{
			char linkFilePath[PATH_SIZE] = {'\0'};
			char actualFilePath[PATH_SIZE] = {'\0'};

			snprintf(linkFilePath, PATH_SIZE, "%s%s", dirPath, dirEntry->d_name);

			if(readlink(linkFilePath, actualFilePath, sizeof(actualFilePath)) == -1)
			{
				perror(linkFilePath);
				continue;;
			}

			for(int i = 0; i < ((depth +1) * 2); i++)
				putchar(' ');
			printf("%s %s -> %s\n", getDeviceTypeMarker(dirEntry->d_type), dirEntry->d_name, actualFilePath);
		}
		else
		{
			for(int i = 0; i < ((depth +1) * 2); i++)
				putchar(' ');
			printf("%s %s\n", getDeviceTypeMarker(dirEntry->d_type), dirEntry->d_name);
		}
	}

	closedir(directory);
	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <directory path>\n", argv[0]);
		return -1;
	}

	if(!treeList(argv[1], 0))
		return -2;

	return 0;
}
