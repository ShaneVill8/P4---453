#ifndef LIBDISK_H
#define LIBDISK_H

#define BLOCKSIZE 256
#define DEFAULT_DISK_SIZE 10240
#define DEFAULT_DISK_NAME “tinyFSDisk” 	
typedef int fileDescriptor;

struct node {
	struct node *next;
	char buffer[256];
};

struct linked_List {
	struct node *head;
	struct node *tail;
	int size;
};

// Libdisk Interface (Phase 1) functions
int openDisk(char *filename, int nBytes);
int readBlock(int disk, int bNum, void *block);
int writeBlock(int disk, int bNum, void *block);
int closeDisk(int disk);

// TinyFS Implementation Functions (Phase 2)
int tfs_mkfs(char *filename, int nBytes);
int tfs_mount(char *filename);
int tfs_unmount();
int tfs_openFile(char *name);
int tfs_closeFile(int FD);
int tfs_writeFile(int FD, char *buffer, int size);
int tfs_deleteFile(int FD);
int tfs_readByte(int FD, char *buffer);
int tfs_seek(int FD, int offset);

//Linked List insert/remove functions
void insertEndLinkedList(struct node *node, struct linked_List *list);
void insertFrontLinkedList(struct node *node, struct linked_List *list);
void removeHeadLinkedList(struct linked_List *list);
void removeTailLinkedList(struct linked_List *list);



#endif