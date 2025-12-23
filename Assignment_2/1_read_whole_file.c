/************************************************************

  1) Read Whole File
	• Accept file name and print full content on console.
	• Use a buffer loop (read() until 0).
	• Show total bytes read.

************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>

#define BLOCK_SIZE 1024

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <file path>\n", argv[0]);
		return -1;
	}

	int fd = open(argv[1], O_RDONLY);

	if(fd == -1)
	{
		perror("Unable to open the file");
		return -2;
	}

	char* buffer[BLOCK_SIZE] = {'\0'};
	int totalNumberOfBytesRead = 0, iRet = 0;

	while((iRet = read(fd, buffer, BLOCK_SIZE)))
	{
		totalNumberOfBytesRead += iRet;
	}

	printf("Total number of bytes read: %d\n", totalNumberOfBytesRead);

	return 0;
}
