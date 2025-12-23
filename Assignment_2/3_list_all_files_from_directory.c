/***********************************************************************

  3) List All Files From Directory
	• Accept directory name.
	• Use opendir() / readdir() to print only names (skip . and ..).

***********************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: Missing arguments", argv[0]);
		printf("Usage: %s <directory path>", argv[0]);
		return -1;
	}

	DIR* directory = opendir(argv[1]);

	if(directory == NULL)
	{
		perror("Unable to open the directory");
		return -2;
	}

	printf("List of the files in the directory %s:\n", argv[1]);
	struct dirent* dirEntry = NULL;
	while((dirEntry = readdir(directory)) != NULL)
	{
		if(dirEntry->d_name[0] == '.')
		{
			continue;
		}
		printf("%s\n", dirEntry->d_name);
	}

	return 0;
}
