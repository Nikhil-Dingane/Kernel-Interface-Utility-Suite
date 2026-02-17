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

//	./lsx -i
//	argv[0]   argv[1]
//	argc = 1  argc[1]

/*
	Open the current directory(".")
	read all entries from that directory
	print the name of files
	close the directory
*/

int main(int argc, char* argv[])
{
	int option = argc;
	// 1: ls -a
	// 2: ls -i

	if(argc == 1 || (strcmp(argv[1], "-a") == 0))
		option = 1;
	else if(strcmp(argv[1], "-i") == 0)
		option = 2;
	else
	{
		errno = EINVAL;
		perror(argv[0]);
		return -1;
	}
		

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
		if(option == 1)
			printf("%s\n", dobj->d_name);
		else if(option == 2)
			printf("%ld\t%s\n", dobj->d_ino, dobj->d_name);
	}

	closedir(dp);
	return 0;
}
