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

//	./statx  FileName
//	argv[0]   argv[1]
//	argc = 2

/*
	Accept file name from command line
	Check whether file exists or not using access
	If does not exist
		print error and exit
	call stat system call to get the files meta data
	Display the meta data
*/

//       #include <sys/stat.h>
//
//       struct stat {
//           dev_t      st_dev;      /* ID of device containing file */
//           ino_t      st_ino;      /* Inode number */
//           mode_t     st_mode;     /* File type and mode */
//           nlink_t    st_nlink;    /* Number of hard links */
//           uid_t      st_uid;      /* User ID of owner */
//           gid_t      st_gid;      /* Group ID of owner */
//           dev_t      st_rdev;     /* Device ID (if special file) */
//           off_t      st_size;     /* Total size, in bytes */
//           blksize_t  st_blksize;  /* Block size for filesystem I/O */
//           blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */
//
//           /* Since POSIX.1-2008, this structure supports nanosecond
//              precision for the following timestamp fields.
//              For the details before POSIX.1-2008, see VERSIONS. */
//
//           struct timespec  st_atim;  /* Time of last access */
//           struct timespec  st_mtim;  /* Time of last modification */
//           struct timespec  st_ctim;  /* Time of last status change */
//
//       #define st_atime  st_atim.tv_sec  /* Backward compatibility */
//       #define st_mtime  st_mtim.tv_sec
//       #define st_ctime  st_ctim.tv_sec
//       };
//

int main(int argc, char* argv[])
{
	struct stat sobj;

	if(argc != 2)
	{
		errno = EINVAL;
		perror(argv[0]);
		printf("Usage: %s <file name>\n", argv[0]);
		return -1;
	}

	errno = 0;
	if(access(argv[1], F_OK) == -1)
	{
		perror(argv[1]);
		return -1;
	}

	errno = 0;
	if(stat(argv[1], &sobj) == -1)
	{
		perror(argv[1]);
		return -1;
	}

	printf("File name: %s\n", argv[1]);
	printf("File size: %ld\n", sobj.st_size);
	printf("Inode number: %ld\n", sobj.st_ino);

	return 0;
}
