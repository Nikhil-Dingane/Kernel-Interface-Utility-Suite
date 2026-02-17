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

//	./touchx  FileName
//	argv[0]   argv[1]
//	argc = 2

/*
	Accept file name from command line
	Check whether file exists or not
	If exist
		just return
	Else
		Create that file 
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

	if(access(argv[1], F_OK) == 0)
	{
		return 0;
	}

	errno = 0;
	if(creat(argv[1], 0777) == -1)
	{
		perror(argv[1]);
		return -1;
	}

	return 0;
}
