#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include <sys/utsname.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

//	./psx
//	argv[0]
//	argc = 1

/*
	Opne the directory /proc
	Open all subdirectors whose name is integer
	Inside that directory open comm file
	Display the name inside that file
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	struct utsname unameobj;
	
	errno = 0;
	if(uname(&unameobj) == -1)
	{
		perror(argv[0]);
		return -1;
	}

	printf("%s %s %s %s %s", unameobj.sysname, unameobj.nodename, unameobj.release, unameobj.version, unameobj.machine);
#ifdef _GNU_SOURCE
	printf(" %s", unameobj.domainname)
#endif
	printf("\n");

	return 0;
}
