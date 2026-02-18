#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

//	./rmx		FileName
//	argv[0]   	argv[1]

//	argc = 2

/*
*/

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file name>\n", argv[0]);
		return -1;
	}

	if(unlink(argv[1]) == -1)
	{
		perror(argv[0]);
		return -1;
	}

	return 0;
}
