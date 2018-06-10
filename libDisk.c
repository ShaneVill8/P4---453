#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "libDisk.h"

char block[BLOCKSIZE];
char* MFS = NULL;

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


/* Phase 2 Functions */
/* Makes blank filesystem of nBytes size on specified file */
int tfs_mkfs(char *filename, int nBytes){

   int numBlocks;
   int i;
   int diskNum = openDisk(filename, nBytes);
   if (diskNum < 0){
      return -1;
   }
   for (i = 0; i < BLOCKSIZE; i++) {
      block[i] = 0x00;
   }

   block[0] = 1;
   block[1] = 0x45;
   block[2] = 1;

   if (writeBlock(diskNum, 0, block) == -1){
      return -1; //error
   }

   for (i = 0; i < BLOCKSIZE; i++) {
      block[i] = 0x00;
   }

   block[0] = 2;
   block[1] = 0x45;
   block[2] = 2;

   if(writeBlock(diskNum, 1, block) == -1){
      return -1; //error
   }

   numBlocks = nBytes/BLOCKSIZE;

   for(i = 3; i < numBlocks; i++){

      for(j = 0; j < BLOCKSIZE; j++){
         block[j] = 0x00;
      }

      block[0] = 4;
      block[1] = 0x45;
      block[2] = j;

      if(writeBlock(diskNum, i-1, block) == -1){
         return -1; //error
      }
   }

   for (i = 0; i < BLOCKSIZE; i++) {
      block[i] = 0x00;
   }

   block[0] = 4;
   block[1] = 0x45;
   block[2] = 0;

   if(writeBlock(diskNum, numBlocks-1, block) == -1){
      return -1; //error
   }

   return 0;
}

/* Mounts a file system to the given file */
int tfs_mount(char *filename){
   char buffer[BLOCKSIZE];
   int diskNum;

   diskNum = openDisk(filename, 0);
   if(readBlock(diskNum, 0, buffer) == -1){
      return -1;
   }

   if (buffer[1] != 0x45){
      return UNKOWN_FS;
   }

   MFS = filename;
   return 0;
}

/* Unmounts the currently mounted file system */
int tfs_unmount(){
   MFS = NULL;
   return 1;
}

/* Opens a file for reading and writing on currently mounted file system */
int tfs_openFile(char *name)
{
   //
   return -1;
}

/* Close file, de-allocate resources, remove table entry */
int tfs_closeFile(int FD)
{
   //
   return -1;
}

/* Writes buffer to the file starting at position 0 in the file */
int tfs_writeFile(int FD, char *buffer, int size)
{
   //
   return -1;
}

/* Deletes a file and marks its blocks as free on disk */
int tfs_deleteFile(int FD)
{
   //
   return -1;
}

/* Reads one byte from the file and copies it to the buffer */
int tfs_readByte(int FD, char *buffer)
{
   //
   return -1;
}

/* Changes the file pointer location to offset */
int tfs_seek(int FD, int offset)
{
   //
   return -1;
}


/* End Phase 2 functions */


/* Linked List Functions */
/* Inserts the node at the end of the given linked list */
void insertEndLinkedList(struct node *node, struct linked_List *list)
{
   if (list->size == 0)
   {
      list->head = node;
      list->tail = node;
      list->tail->next = NULL;
      list->size++;
   }
   else
   {
      list->tail->next = node;
      list->tail = node;
      list->size++;
      list->tail->next = NULL;
   }
}

/* Inserts the node to the front of the given linked list */
void insertFrontLinkedList(struct node *node, struct linked_List *list)
{
   if (list->size == 0) // The new node is the head and the tail
   {
      list->head = node;
      list->tail = node;
      list->tail->next = NULL;
      list->size++;
   }
   else
   {
      node->next = list->head;
      list->head = node;
      list->size++;
   }
}

/* Removes the head from the given linked list */
void removeHeadLinkedList(struct linked_List *list)
{
   struct node *tmp;
   if (list->size == 1)
   {
      tmp = list->head; 
      list->head = NULL;
      list->tail = NULL;
      list->size--;
      free(tmp); 
   }
   else if (list->size > 0)
   {
      tmp = list->head; 
      list->head = list->head->next;
      list->size--;
      free(tmp);
   }
}

/* Removes the tail from the given linked list */
void removeTailLinkedList(struct linked_List *list)
{
   struct node *tmp;
   if (list->size == 1)
   {
      tmp = list->head; 
      list->head = NULL;
      list->tail = NULL;
      list->size--;
      free(tmp); 
   }
   else if (list->size > 0)
   {
      tmp = list->head; 
      while (tmp->next->next != NULL)
      {
         tmp = tmp->next;
      }
      list->tail = tmp;
      list->size--;
      free(tmp->next);
      tmp->next = NULL;
   }
}
/* End Linked List functions */