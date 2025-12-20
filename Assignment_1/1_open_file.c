#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>

/*

  1) Open File
	• Accept file name from user and open it using open().
	• Print: success message + returned file descriptor.
	• Handle errors using perror().

*/

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: missing arguments\n", argv[0]);
		printf("Usage: %s <file name to open> \n", argv[0]);
		return -1;
	}
	
	int fd = 0;

	fd = open(argv[1], O_RDONLY);

	if(fd == -1)
	{
		perror("Unable to open file ");
		return -2;
	}

	printf("%s file successfully opened with fd: %d\n", argv[1], fd);
	close(fd);

	return 0;
}
