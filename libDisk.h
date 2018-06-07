#ifndef LIBDISK_H
#define LIBDISK_H

#define BLOCKSIZE 256
#define DEFAULT_DISK_SIZE 10240
#define DEFAULT_DISK_NAME “tinyFSDisk” 	
typedef int fileDescriptor;

int openDisk(char *filename, int nBytes);
int readBlock(int disk, int bNum, void *block);
int writeBlock(int disk, int bNum, void *block);
int closeDisk(int disk);

#endif