#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

typedef int BOOL;

#define TRUE 1
#define FALSE 0

#define BUFFER_SIZE 4096

//	./touchx  FileName  -n       number
//	argv[0]   argv[1]   argv[2]  argv[3]
//	argc = 4

int main(int argc, char* argv[])
{
	if(argc < 2 || (argc > 2 && argc != 4))
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file name> [-n <lines>]\n", argv[0]);
		return -1;
	}

	int fd = 0, ret_val = 0;
	char buffer[BUFFER_SIZE] = {'\0'};
	int linesToRead = 10, lines = 0;
	int pos = 0, fileSize = 0, buffSizeToRead = 0;

	if(argc == 4 )
	{
		if(strncmp(argv[2], "-n", 2) != 0)
		{
			errno = EINVAL;
			perror(argv[0]);
			printf("Usage: %s <file name> [-n <lines>]\n", argv[0]);
			return -1;
		}
		else
			linesToRead = atoi(argv[3]);
	}
	
	if(linesToRead <= 0)
		return 0;

	errno = 0;
	if((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror(argv[1]);
		return -1;
	}

	errno = 0;
	if((fileSize = lseek(fd, 0, SEEK_END)) == -1)
	{
		printf("%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		return -1;
	}
	pos = fileSize;
	BOOL shouldStop = FALSE;

	// If file doesn't end with newline, count the last line upfront.
	if(fileSize > 0)
	{
		char lastChar = '\0';
		errno = 0;
		if(pread(fd, &lastChar, 1, fileSize - 1) == 1)
		{
			if(lastChar != '\n')
				lines = 1;
		}
		else if(errno)
		{
			printf("%s: %s: %s\n", argv[0], argv[1], strerror(errno));
			return -1;
		}
	}

	while(pos > 0 && lines <= linesToRead && !shouldStop)
	{
		if(pos > BUFFER_SIZE)
		{
			buffSizeToRead = BUFFER_SIZE;
			pos = pos - BUFFER_SIZE;
		}
		else
		{
			buffSizeToRead = pos;
			pos = 0;
		}

		errno = 0;
		if((ret_val = pread(fd, buffer, buffSizeToRead, pos)) == 0)
			break;

		for(int i = (ret_val -1); i >= 0; i--)
		{
			if(buffer[i] == '\n')
			{
				lines++;

				if(lines > linesToRead)
				{
					pos = pos + i + 1;
					shouldStop = TRUE;
					break;
				}
			}
		}
		memset(buffer, '\0', BUFFER_SIZE);
	}

	if(errno)
	{
		printf("%s: %s\n", argv[0], strerror(errno));
		return -1;
	}

	errno = 0;
	if((fileSize = lseek(fd, pos, SEEK_SET)) == -1)
	{
		printf("%s: %s: %s\n", argv[0], argv[1], strerror(errno));
		return -1;
	}

	errno = 0;
	while((ret_val = read(fd, buffer, BUFFER_SIZE)) != 0)
	{
		if(errno)
		{
			printf("%s: %s: %s\n", argv[0], argv[1], strerror(errno));
			return -1;
		}
		write(STDOUT_FILENO, buffer, ret_val);
		memset(buffer, '\0', BUFFER_SIZE);
	}
	close(fd);
	return 0;
}
