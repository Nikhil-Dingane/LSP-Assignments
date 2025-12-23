/******************************************************************************************

  5) Find Largest File in Directory
	• Accept directory name.
	• Find and print:
	• largest file name
	• its size in bytes
	• Consider only regular files (ignore directories).

******************************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <directory path>\n", argv[0]);
		return -1;
	}

	DIR* directory = opendir(argv[1]);

	if(directory == NULL)
	{
		perror("Unable to open the directory");
		return -2;
	}

	off_t largestFileSize = 0;
	char* largestSizeFileName;
	struct dirent* dirEntry = NULL;
	struct stat fileStat;
	while((dirEntry = readdir(directory)) != NULL)
	{
		if(dirEntry->d_type != DT_REG)
			continue;

		if(stat(dirEntry->d_name, &fileStat) == -1)
		{
			perror("Unable to get the stat of the file");
			printf("File name: %s", dirEntry->d_name);
			continue;
		}
		if(fileStat.st_size > largestFileSize)
		{
			largestFileSize = fileStat.st_size;
			largestSizeFileName = dirEntry->d_name;
		}
	}

	printf("Largest file size: %ld bytes\n", largestFileSize);
	printf("Largest size file name: %s\n", largestSizeFileName);

	return 0;
}
