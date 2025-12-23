/*****************************************************************

  5) Read N Bytes From File
	• Accept file name and number of bytes N.
	• Read exactly N bytes using read() and print on console.
	• If file contains less than N, print only available bytes

*****************************************************************/

#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("%s: <file path> <number of bytes to be read>\n", argv[0]);
		return -1;
	}

	int fd = 0;

	fd = open(argv[1], O_RDONLY);

	if(fd == -1)
	{
		perror("Unable to open file");
		return -1;
	}

	char *endptr;
	errno = 0;
	int noOfBytes = strtol(argv[2], &endptr, 10);
	if (errno != 0 || endptr == argv[2] || *endptr != '\0' || noOfBytes <= 0)
	{
		printf("Invalid number of bytes: %s\n", argv[2]);
		return -2;
	}

	char* buffer = (char*)malloc(noOfBytes);
	memset(buffer, '\0', noOfBytes);

	int iRet = read(fd, buffer, noOfBytes);

	printf("File Data: \n%s\n", buffer);

	return 0;
}
