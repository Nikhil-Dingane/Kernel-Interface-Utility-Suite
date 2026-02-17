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


//	./mvx		SourcePath		DestPath
//	argv[0]		argv[1]			argv[2]

//	argc = 3

int main(int argc, char* argv[])
{
	int dstFileFd, srcFileFd;

	if(argc != 3)
	{
		printf("%s: Missing arguments\n", argv[0]);
		printf("Usage: %s <source file path> <destination file path>\n", argv[0]);
		return -1;
	}

	if(rename(argv[1], argv[2]) == -1)
	{
		perror(argv[0]);
		return -1;
	}

	return 0;
}
