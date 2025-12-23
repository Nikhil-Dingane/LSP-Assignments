/************************************************************************************************

  4) Display Complete File Information
	• Accept file name and display file metadata using stat():
	• Size, inode, permissions, hard links, owner uid/gid, file type, last access/modify time.

*************************************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>
#include<time.h>

void printFilePermissions(struct stat* fileStat)
{
	printf((fileStat->st_mode & S_IRUSR ? "r" : "-"));
	printf((fileStat->st_mode & S_IWUSR ? "w" : "-"));
	printf((fileStat->st_mode & S_IXUSR ? "x" : "-"));
	printf((fileStat->st_mode & S_IRGRP ? "r" : "-"));
	printf((fileStat->st_mode & S_IWGRP ? "w" : "-"));
	printf((fileStat->st_mode & S_IXGRP ? "x" : "-"));
	printf((fileStat->st_mode & S_IROTH ? "r" : "-"));
	printf((fileStat->st_mode & S_IWOTH ? "w" : "-"));
	printf((fileStat->st_mode & S_IXOTH ? "x" : "-"));
	printf("\n");
}

void printDeviceType(struct stat* fileStat)
{
	switch (fileStat->st_mode & S_IFMT)
	{
		case S_IFBLK:  printf("block device\n");            break;
		case S_IFCHR:  printf("character device\n");        break;
		case S_IFDIR:  printf("directory\n");               break;
		case S_IFIFO:  printf("FIFO/pipe\n");               break;
		case S_IFLNK:  printf("symlink\n");                 break;
		case S_IFREG:  printf("regular file\n");            break;
		case S_IFSOCK: printf("socket\n");                  break;
		default:       printf("unknown?\n");                break;
	}
}

void printFileStats(struct stat* fileStat)
{
	printf("File Size: 		  	%ld\n", fileStat->st_size);
	printf("Inode Number: 		  	%ld\n", fileStat->st_ino);
	printf("Permissions: 		 	");
	printFilePermissions(fileStat);
	printf("Hard links: 			%ld\n", fileStat->st_nlink);
	printf("UID: 				%d\n", fileStat->st_uid);
	printf("GID: 				%d\n", fileStat->st_gid);
	printf("File type: 			");
	printDeviceType(fileStat);
	printf("Last status change:       	%s", ctime(&(fileStat->st_ctime)));
	printf("Last file access:         	%s", ctime(&(fileStat->st_atime)));
	printf("Last file modification:   	%s", ctime(&(fileStat->st_mtime)));
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("%s: <file path>\n", argv[0]);
		return -1;
	}

	struct stat fileStat;
	int iRet = stat(argv[1], &fileStat);

	if(iRet == -1)
	{
		perror("Error in getting stat");
		return -2;
	}

	printFileStats(&fileStat);

	return 0;
}
