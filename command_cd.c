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

//	./cdx     Path
//	argv[0]   argv[1]
//	argc = 2

/*
	Get new directory path
	Call chdir with that
	call getwed to check the changed patth
*/

int main(int argc, char* argv[])
{
	char buffer[1024] = {'\0'};

	if(argc != 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <Path>\n", argv[0]);
		return -1;
	}

	errno = 0;
	if(chdir(argv[1]) == -1)
	{
		perror(argv[0]);
		return -1;
	}

	if(getcwd(buffer, sizeof(buffer) - 1) == NULL)
	{
		perror(argv[0]);
		return -1;
	}

	printf("%s\n", buffer);

	return 0;
}
