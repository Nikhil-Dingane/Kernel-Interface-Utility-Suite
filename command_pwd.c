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

//	./pwdx
//	argv[0]
//	argc = 1

/*
	Call the system call getcwd
	Print the result of getcwd
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	char buffer[1024] = {'\0'};

	errno = 0;
	if(getcwd(buffer, sizeof(buffer)) == NULL)
	{
		perror("pwdx");
	}

	printf("%s\n", buffer);

	return 0;
}
