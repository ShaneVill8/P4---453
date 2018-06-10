#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "libDisk.h"


int tfs_mkfs(char *filename, int nBytes){

}

int tfs_mount(char *filename){

}

int tfs_unmount(void){

}

fileDescriptor tfs_openFile(char *name){

}

int tfs_closeFile(fileDescriptor FD){

}

int tfs_writeFile(fileDescriptor FD, char *buffer, int size){

}

int tfs_deleteFile(fileDescriptor FD){

}

int tfs_readByte(fileDescriptor FD, char *buffer){

}

int tfs_seek(fileDescriptor FD, int offset){

}
