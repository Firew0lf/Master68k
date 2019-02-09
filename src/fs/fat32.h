#ifndef FAT32_H
#define FAT32_H

#include <blockDevice.h>

typedef struct {
	BLOCK_DEVICE* bdev;
	unsigned int startingBlock; // first block of the FS
} FS_FAT32;

typedef struct {
	// FAT12/16/32
	int jump: 24;
	char formatter[8];
	short bytesPerSector;
	unsigned char reservedSectors;
	unsigned char fatAmount;
	unsigned short rootSize_old; // should be 0 for FAT32
	unsigned short sectors_old; // should be 0 for FAT32
	unsigned char diskType; // 0xF8 for HDD, 0xF0 for floppies
	unsigned short fatSize_old; // should be 0 for FAT32
	unsigned short sectorsPerTrack;
	unsigned short headAmount;
	unsigned int hiddenSectors; // 0 by default
	unsigned int sectorAmount;
	// FAT32
	unsigned int fatSize;
	unsigned short diskAttributes;
	unsigned short fsVersion; // 0 by default
	unsigned int firstRootCluster;
	unsigned short fsInfos; // 0 by default
	unsigned char diskId;
	unsigned char _reserved;
	unsigned char signature; // 0x29 by default
	unsigned int serialNumber;
	unsigned char name[11]; // "NO NAME    " by default
	unsigned char fsType[8]; // should be "FAT32   "
} FS_FAT32_HEADER;

#endif
