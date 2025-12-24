/**********************************************************************

  1) Copy File Contents (source → destination)
	• Accept source_file and dest_file.
	• Create destination if not exists (O_CREAT | O_TRUNC).
	• Copy using buffered read()/write() loop.
	• Preserve permissions (optional bonus using stat() + chmod()).

**********************************************************************/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>

#define BLOCK_SIZE 1024

#define TRUE 1
#define FALSE 0

typedef int BOOL;

BOOL copyData(int srcFileFd, int dstFileFd)
{
	char buffer[BLOCK_SIZE] = {'\0'};
	int iRet = 0;

	while((iRet = read(srcFileFd, buffer, BLOCK_SIZE)) != 0)
	{
		if(errno)
		{
			perror("Unable to read from the source file");
			return FALSE;
		}

		write(dstFileFd, buffer, iRet);

		if(errno)
		{
			perror("Unable to write to the destination file");
			return FALSE;
		}

		memset(buffer, '\0', BLOCK_SIZE);
	}

	return TRUE;
}

BOOL copyFilePermissions(int srcFileFd, int dstFileFd)
{
	struct stat fileStat;

	if(fstat(srcFileFd, &fileStat) == -1)
	{
		perror("Unable to get the stat of source file");
		return FALSE;
	}

	if(fchmod(dstFileFd, fileStat.st_mode) == -1)
	{
		perror("Unable to change the mode of destination file");
		return FALSE;
	}

	return TRUE;
}

int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <source file path> <destination file path>\n", argv[0]);
		return -1;
	}

	int dstFileFd, srcFileFd;

	if((srcFileFd = open(argv[1], O_RDONLY)) == -1)
	{
		perror("Unable to open the destination file");
		return -2;
	}

	if((dstFileFd = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, 0777)) == -1)
	{
		perror("Unable to open the source file");
		return -3;
	}

	if(!copyData(srcFileFd, dstFileFd))
		return -4;

	printf("Content of file %s is successfully copied to file %s\n", argv[1], argv[2]);

	if(!copyFilePermissions(srcFileFd, dstFileFd))
		return -5;

	printf("Destination file %s mode has been synced with source file %s\n", argv[1], argv[2]);

	close(srcFileFd);
	close(dstFileFd);

	return 0;
}
