/**********************************************************

  2) Check File Present in Directory
	• Accept directory name and file name.
	• Check whether that file exists in that directory.
	• Print absolute matched path if found.

**********************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
#include<errno.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <dir path> <file path>\n", argv[0]);
		return -1;
	}

	DIR* directory;

	if((directory = opendir(argv[1])) == NULL)
	{
		perror("Unable to open the directory");
		return -1;
	}

	struct dirent* dirEntry;

	errno = 0;
	while(((dirEntry = readdir(directory)) != NULL) && errno == 0)
	{
		if(strcmp(dirEntry->d_name, argv[2]) == 0)
		{
			break;
		}
	}

	if(errno)
	{
		perror("Error while reading the directory entries");
		return -2;
	}

	if(dirEntry)
		printf("file %s is exist in the directory %s\n", argv[2], argv[1]);
	else
		printf("file %s does not exist in the directory %s\n", argv[2], argv[1]);

	return 0;
}
