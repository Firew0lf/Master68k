#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "blockDevice.h"

/***
FS structure:
 - Layer 0: physical drive
 - Layer 1: drive driver
 - Layer 2: block device, partition detection
  -> Read/Write/Flush sectors
 - Layer 3: filesystem
  -> Open/Close/List/Create/Remove files
 - Layer 4: file
  -> Read/Write data
*/

typedef unsigned int inode_t;

typedef struct {
	inode_t inode;
	char mode; // 'r', 'w', 'a', y'all know that
	int seek;
	int id;
} FILE;

typedef enum {
	FILE,
	DIRECTORY,
	LINK,
	// uncommon
	DEVICE,
	BLOCK_DEVICE,
} DIR_ENTRY_TYPE;

typedef enum {
	READ    = 1<<0,
	WRITE   = 1<<1,
	EXECUTE = 1<<2,
	HIDDEN  = 1<<3,
} DIR_ENTRY_ATTRIBUTES;

typedef struct {
	DIR_ENTRY* next; // NULL if last one
	char* name;
	DIR_ENTRY_TYPE type;
	DIR_ENTRY_ATTRIBUTES attributes;
} DIR_ENTRY;

typedef struct {
	FILE* (*open)(const char* filename, const char* mode);
	int (*close)(FILE* file);
	size_t (*read)(void* buffer, size_t size, size_t count, FILE* file);
	size_t (*write)(void* buffer, size_t size, size_t count, FILE* file);
	
} FILESYSTEM;

#endif
