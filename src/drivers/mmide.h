/***
Memory-mapped IDE disk driver
*/

#ifndef MM_IDE_H
#define MM_IDE_H

typedef enum {
	AMNF = 1<<0, // Address Mark Not Found
	T0NF = 1<<1, // Track 0 Not Found
	ABRT = 1<<2, // command ABoRTed
	_UN1 = 1<<3, // unused bit 1
	IDNF = 1<<4, // ID Not Found
	_UN2 = 1<<5, // unused bit 2
	UNC  = 1<<6, // UNCorrectable error
	BK   = 1<<7, // Bad Block
} MM_IDE_disk_error;

typedef enum {
	ERROR = 1<<0, // error in the previous command
	INDEX = 1<<1, // index mark detected (used for RPM counting)
	CORR  = 1<<2, // correctable data error encountered
	DRQ   = 1<<3, // data request
	DSC   = 1<<4, // Drive Seek Complete
	DWF   = 1<<5, // Drive Write Fail
	DRDY  = 1<<6, // Drive Ready to accept commands
	BUSY  = 1<<7, // drive busy
} MM_IDE_disk_status;

// As seen in memory space
// Only the dataPort is 16-bits wide, the others are shorts for padding
typedef struct {
	unsigned short dataPort;
	
	union {
		unsigned short error; // read
		unsigned short write_precomp; // write
	};
	
	unsigned short sectorCount;
	unsigned short sectorNumber;
	unsigned short cylinderlow;
	unsigned short cylinderhigh;
	unsigned short driveHead;
	
	union {
		unsigned short status;
		unsigned short command;
	};
	
} MM_IDE_DISK_SPACE;

typedef struct {
	MM_IDE_DISK_SPACE* base_addr; // total disk address space is 8 bytes
	unsigned int buffered_sector;
	unsigned char buffer[512]; // 512 bytes sector buffer
} MM_IDE_DISK;

/***
Initialises the IDE disk.
`base_addr` must be set before calling this function.
*/
bool MM_IDE_init(MM_IDE_DISK* d);

/***
Read a sector with LBA addressing.
Data is put in the disk structure buffer.
*/
int MM_IDE_readSector(MM_IDE_DISK* d, unsigned int lba, unsigned char** data);

/***
Write a sector with LBA addressing.
*/
int MM_IDE_writeSector(MM_IDE_DISK* d, unsigned int lba, unsigned char* data);

/***
Flush the sector stored in the buffer to the disk.
*/
int MM_IDE_flushSector(MM_IDE_DISK* d);

#endif
