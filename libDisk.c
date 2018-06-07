#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "libDisk.h"

int openDisk(char *filename, int nBytes){
	int fd, i;
	char buffer[nBytes];
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	if(nBytes < 0 || filename == NULL){
		return -1;
	}

	if(nBytes == 0){
		fd = open(filename, O_RDWR);
		if(fd == -1){
			return -1;
		}
	}
	else{
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
		if(fd == -1){
			return -1;
		}

		for(i = 0; i < nBytes; i++){
			buffer[i] = 0;
		}
		write(fd, buffer, nBytes);
	}
	return fd;
}

int readBlock(int disk, int bNum, void *block){
	if(lseek(disk, bNum * BLOCKSIZE, SEEK_SET) == -1){
		return -1;
	}
	if(read(disk, block, BLOCKSIZE) == -1){
		return -1;
	}
	return 0;
}

int writeBlock(int disk, int bNum, void *block){
	if(lseek(disk, bNum * BLOCKSIZE, SEEK_SET) == -1){
		return -1;
	}
	if(write(disk, block, BLOCKSIZE) == -1){
		return -1;
	}
	return 0;
}

int closeDisk(int disk){
	return close(disk);
}