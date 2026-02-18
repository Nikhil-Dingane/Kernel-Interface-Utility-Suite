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

//	./wcx	  FileName
//	argv[0]   argv[1]
//	argc = 2
//
//	./wcx	  -lwc	 FileName
//	argv[0]   argv[1]   argv[2]
//	argc = 3
//
//	./wcx	  FileName  -lwc
//	argv[0]   argv[1]   argv[2]
//	argc = 3

/*
	Accept file name from command line
	Count lines, words, and bytes
	Print the counts as per options
*/

#define MAX_BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
	if(argc < 2 || argc > 3)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file name> [-clw]\n", argv[0]);
		return -1;
	}

	int fd = 0, iRet = 0;
	char buffer[MAX_BUFFER_SIZE] = {'\0'};
	memset(buffer, '\0', MAX_BUFFER_SIZE);

	int showLines = 0, showWords = 0, showBytes = 0;
	char* fileName = NULL;

	if(argc == 2)
	{
		showLines = 1;
		showWords = 1;
		showBytes = 1;
		fileName = argv[1];
	}
	else
	{
		char* optArg = NULL;
		char* fileArg = NULL;

		if(argv[1][0] == '-')
		{
			optArg = argv[1];
			fileArg = argv[2];
		}
		else if(argv[2][0] == '-')
		{
			optArg = argv[2];
			fileArg = argv[1];
		}
		else
		{
			errno = EINVAL;
			perror(argv[0]);
			printf("Usage: %s <file name> [-clw]\n", argv[0]);
			return -1;
		}

		for(int i = 1; optArg[i] != '\0'; i++)
		{
			switch(optArg[i])
			{
				case 'c':
					showBytes = 1;
					break;
				case 'l':
					showLines = 1;
					break;
				case 'w':
					showWords = 1;
					break;
				default:
					errno = EINVAL;
					perror(argv[0]);
					printf("Usage: %s <file name> [-clw]\n", argv[0]);
					return -1;
			}
		}
		fileName = fileArg;
	}

	errno = 0;
	if((fd = open(fileName, O_RDONLY)) == -1)
	{
		perror(fileName);
		return 0;
	}

	unsigned long long lines = 0, words = 0, bytes = 0;
	int inWord = 0;

	errno = 0;
	while((iRet = read(fd, buffer, sizeof(buffer))) != 0)
	{
		bytes = bytes + iRet;
		for(int i = 0; i < iRet; i++)
		{
			if(buffer[i] == '\n')
				lines++;

			if(isspace((unsigned char)buffer[i]))	
			{
				if(inWord)
					inWord = 0;
			}
			else
			{
				if(!inWord)
				{
					words++;
					inWord = 1;
				}
			}
		}
		memset(buffer, '\0', MAX_BUFFER_SIZE);
	}

	if(errno)
	{
		perror(fileName);
		return -2;
	}

	if(showLines)
		printf("%llu ", lines);
	if(showWords)
		printf("%llu ", words);
	if(showBytes)
		printf("%llu ", bytes);
	printf("%s\n", fileName);

	close(fd);
	return 0;
}
