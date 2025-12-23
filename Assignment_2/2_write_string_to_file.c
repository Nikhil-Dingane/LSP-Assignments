/*************************************************************

  2) Write String to File
	• Accept file name and a string from user.
	• Write string using write() (append mode by default).
	• Print number of bytes written.

*************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <file path> <string to write>\n", argv[0]);
		return -1;
	}

	int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND);

	if(fd == -1)
	{
		perror("Unable to open the file");
		return -2;
	}

	int iRet = write(fd, argv[2], strlen(argv[2]));

	if(iRet == -1)
	{
		perror("Unable to write in the file");
		return -3;
	}

	printf("%d bytes successfully has been written to the file\n", iRet);

	return 0;
}
