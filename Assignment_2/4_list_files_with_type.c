/******************************************************************************************

  3) List Files with Type
	• Accept directory name.
	• Print each entry with its type: Regular / Directory / Link / FIFO / Socket / Char / Block
	• Use lstat() for accurate type.

******************************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<stdlib.h>

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

	struct dirent* dirEntry = NULL;

	printf("%-50s%-20s", "File Name", "File Type");
	printf("\n\n");

	while((dirEntry = readdir(directory)) != NULL)
	{
		printf("%-50s%-20s", dirEntry->d_name, getDeviceType(dirEntry->d_type));
		printf("\n");
	}

	return 0;
}
