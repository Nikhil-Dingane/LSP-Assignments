/******************************************************************************************

  1 Directory Traversal Basics
    Create a program ls_clone.c that takes one directory path and prints:
	• Entry name
	• Type (file/dir/link/other)
	• Size (bytes)
	• Permissions in rwxr-xr-x format
	• Last modified time
	• Skip . and ..
	• Build full path using snprintf(dir + "/" + name).

******************************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<time.h>

#define PATH_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

void printFilePermissions(struct stat* fileStat)
{
	printf((fileStat->st_mode & S_IRUSR ? "r" : "-"));
	printf((fileStat->st_mode & S_IWUSR ? "w" : "-"));
	printf((fileStat->st_mode & S_IXUSR ? "x" : "-"));
	printf((fileStat->st_mode & S_IRGRP ? "r" : "-"));
	printf((fileStat->st_mode & S_IWGRP ? "w" : "-"));
	printf((fileStat->st_mode & S_IXGRP ? "x" : "-"));
	printf((fileStat->st_mode & S_IROTH ? "r" : "-"));
	printf((fileStat->st_mode & S_IWOTH ? "w" : "-"));
	printf((fileStat->st_mode & S_IXOTH ? "x" : "-"));
}


char* getDeviceType(unsigned char type)
{
	switch (type)
	{
		case DT_BLK:  return "block device";
		case DT_CHR:  return "character device";
		case DT_DIR:  return "directory";
		case DT_FIFO: return "FIFO/pipe";
		case DT_LNK:  return "symlink";
		case DT_REG:  return "regular file";
		case DT_SOCK: return "socket";
		default:      return "unknown?";
	}
}

BOOL listDir(char *dir)
{
	DIR* directory = opendir(dir);

	if(directory == NULL)
	{
		perror("Unable to open the directory");
		return FALSE;
	}

	struct dirent* dirEntry = NULL;
	printf("%-40s    %-20s    %-15s    %-11s    %-25s\n\n", "Name", "Type", "Size", "Permissions", "Last Modifed Time");
	//printf("\n\n");

	while((dirEntry = readdir(directory)) != NULL)
	{
		if(strcmp(dirEntry->d_name, ".") == 0
		|| strcmp(dirEntry->d_name, "..") == 0)
			continue;

		struct stat fileStat;
		char filePath[PATH_SIZE];
		snprintf(filePath, PATH_SIZE, "%s/%s", dir, dirEntry->d_name);

		if(stat(filePath, &fileStat) == -1)
		{
			perror(filePath);
			return FALSE;
		}

		printf("%-40.40s    ", filePath);
		printf("%-20s    ", getDeviceType(dirEntry->d_type));
		printf("%-15ld    ", fileStat.st_size);
		printFilePermissions(&fileStat);
		printf("      ");
		printf("%-25s", ctime(&(fileStat.st_mtime)));
	}

	closedir(directory);
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

	listDir(argv[1]);

	return 0;
}
