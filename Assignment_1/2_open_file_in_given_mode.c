/********************************************************************************

  2) Open File in Given Mode
	• Accept file name and mode (R, W, RW, A) from user.
	• Convert mode to flags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND | O_CREAT).
	• Open file accordingly and display fd.

********************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

#define IN
#define OUT

typedef int BOOL;

#define TRUE 1
#define FALSE 0

BOOL getFileOpenMode(IN char* modeChars, OUT int* mode, OUT char** fileOpenModeStr)
{
	*fileOpenModeStr = (char *)malloc(50);
	memset(*fileOpenModeStr, '\0', 50);

	if(strcmp(modeChars, "R") == 0)
	{
		*mode = O_RDONLY;
		*fileOpenModeStr = "O_RDONLY";
	}
	else if(strcmp(modeChars, "W") == 0)
	{
		*mode = O_WRONLY;
		*fileOpenModeStr = "O_WRONLY";
	}
	else if(strcmp(modeChars, "WR") == 0)
	{
		*mode = O_RDWR;
		*fileOpenModeStr = "O_RDWR";
	}
	else if(strcmp(modeChars, "A") == 0)
	{
		*mode = O_APPEND | O_CREAT;
		*fileOpenModeStr = "O_APPEND | O_CREAT";
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <file path> <mode>\n", argv[0]);
		return -1;
	}

	int mode;
	char* fileOpenModeStr = NULL;

	if(!getFileOpenMode(argv[2], &mode, &fileOpenModeStr))
	{
		printf("Invalid file open mode\n");
		return -2;
	}

	int fd;

	fd = open(argv[1], mode);

	if(fd == -1)
	{
		perror("Unable to open file");
		printf("File name: %s\n", argv[1]);
		return -3;
	}

	printf("%s file opened in mode: %s and with fd: %d\n", argv[1], fileOpenModeStr, fd);

	return 0;
}
