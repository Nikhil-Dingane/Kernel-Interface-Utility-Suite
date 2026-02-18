#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

#define BUFFER_SIZE 4096

//	./headx  FileName  -n       number
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

	while((ret_val = read(fd, buffer, sizeof(buffer))) != 0)
	{
		for(int i = 0; i < ret_val; i++)
		{
			if(buffer[i] == '\n')
				lines++;
			if(lines >= linesToRead)
			{
				write(STDOUT_FILENO, buffer, i + 1);
				close(fd);
				return 0;
			}
		}
		write(STDOUT_FILENO, buffer, ret_val);
		memset(buffer, '\0', sizeof(buffer));
	}

	close(fd);
	return 0;
}
