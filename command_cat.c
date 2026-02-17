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

//	./catx	  FileName
//	argv[0]   argv[1]
//	argc = 2

/*
	Accept file name from command line
	Check whether file exists or not
	If exist
		print the content on the standard output
	Else
		print error
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file name>\n", argv[0]);
		return -1;
	}

	int fd = 0, iRet = 0;
	char buffer[MAX_BUFFER_SIZE] = {'\0'};
	memset(buffer, '\0', MAX_BUFFER_SIZE);

	errno = 0;
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		return 0;
	}

	errno = 0;
	while((iRet = read(fd, buffer, sizeof(buffer))) != 0)
	{
		//printf("%s", buffer);
		write(1, buffer, iRet);
		memset(buffer, '\0', MAX_BUFFER_SIZE);
	}

	if(errno)
	{
		perror(argv[1]);
		return -2;
	}

	close(fd);
	return 0;
}
