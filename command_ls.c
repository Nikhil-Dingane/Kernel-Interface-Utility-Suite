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

//	./lsx
//	argv[0]
//	argc = 1

/*
	Open the current directory(".")
	read all entries from that directory
	print the name of files
	close the directory
*/

int main(int argc, char* argv[])
{
	int fd = 0, iRet = 0;
	char *path = ".";

	DIR *dp = NULL;

	errno = 0;
	if((dp = opendir(path)) == NULL)
	{
		perror(path);
		return 0;
	}

	struct dirent *dobj;

	while((dobj = readdir(dp)) != NULL)
	{
		printf("%s\n", dobj->d_name);
	}

	closedir(dp);
	return 0;
}
