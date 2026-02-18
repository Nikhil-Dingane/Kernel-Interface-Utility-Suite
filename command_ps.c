#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<stdlib.h>
#include<ctype.h>

#define TRUE 1
#define FALSE 0

typedef int BOOL;

//	./psx
//	argv[0]
//	argc = 1

/*
	Open the directory /proc
	Open all subdirectories whose name is integer
	Inside that directory open comm file
	Display PID and process name
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	DIR *dp = NULL;
	struct dirent *dptr = NULL;
	char path[MAX_BUFFER_SIZE] = {'\0'};
	char buffer[MAX_BUFFER_SIZE] = {'\0'};
	int fd = 0, iRet = 0;
	BOOL isNumeric = TRUE;

	if(argc != 1)
	{
		errno = EINVAL;
		perror(argv[0]);
		return -1;
	}

	errno = 0;
	if((dp = opendir("/proc")) == NULL)
	{
		perror("/proc");
		return -1;
	}

	printf("PID\tCMD\n");

	while(1)
	{
		errno = 0;
		dptr = readdir(dp);
		if(dptr == NULL)
			break;

		isNumeric = TRUE;
		for(int i = 0; dptr->d_name[i] != '\0'; i++)
		{
			if(!isdigit((unsigned char)dptr->d_name[i]))
			{
				isNumeric = FALSE;
				break;
			}
		}

		if(isNumeric == FALSE)
			continue;

		memset(path, '\0', sizeof(path));
		snprintf(path, sizeof(path), "/proc/%s/comm", dptr->d_name);

		errno = 0;
		if((fd = open(path, O_RDONLY)) == -1)
			continue;

		memset(buffer, '\0', sizeof(buffer));
		errno = 0;
		iRet = read(fd, buffer, sizeof(buffer) - 1);
		close(fd);

		if(iRet <= 0)
			continue;

		buffer[iRet] = '\0';
		for(int i = 0; i < iRet; i++)
		{
			if(buffer[i] == '\n')
			{
				buffer[i] = '\0';
				break;
			}
		}

		printf("%s\t%s\n", dptr->d_name, buffer);
	}

	if(errno != 0)
	{
		perror("/proc");
		closedir(dp);
		return -1;
	}

	closedir(dp);
	return 0;
}
