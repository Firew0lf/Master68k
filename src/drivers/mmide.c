#include <stdbool.h>
#include "mmide.h"

// RW registers
#define R_DATAPORT     0
#define R_SECTORCOUNT  2
#define R_SECTORNUMBER 3
#define R_CYLINDERL    4
#define R_CYLINDERH    5
#define R_DRIVE_HEAD   6

// R or W registers
#define R_READ_ERROR    1
#define R_WRITE_PRECOMP 1
#define R_READ_STATUS   7
#define R_WRITE_COMMAND 7

/*inline unsigned char readRegister(MM_IDE_DISK* d, char r) {
	return *((unsigned char*)(((int)(d->base_addr))+r)); // never enough ()
}

inline void writeRegister(MM_IDE_DISK* d, char r, unsigned char v) {
	*((unsigned char*)(((int)(d->base_addr))+r)) = v;
}*/

bool isReady(MM_IDE_DISK* d) {
	return ((d->base_addr->status)&(DRDY))!=0;
}

void waitReady(MM_IDE_DISK* d) {
	for (;isReady(d););
}

void writeLBA(MM_IDE_DISK *d, unsigned int lba) {
	d->base_addr->sectorNumber = lba&0xff; // first 8 bits
	d->base_addr->cylinderlow = (lba>>8)&0xff; // bits 8-15
	d->base_addr->cylinderhigh = (lba>>16)&0xff; // bits 16-23
	d->base_addr->driveHead = (d->base_addr->driveHead&0xf0) | (lba>>23)&0x0f; // bits 24-27
}

bool MM_IDE_init(MM_IDE_DISK* d) {
	waitReady(d);
	// set to LBA mode
	d->base_addr->driveHead |= (1<<6);
	waitReady(d);
}

int MM_IDE_readSector(MM_IDE_DISK* d, unsigned int lba, unsigned char** data) {
	waitReady(d);
	d->base_addr->sectorCount = 1; // only read 1 sector
	writeLBA(d, lba);
	d->base_addr->command = 0x20; // send `read w/ retry` command
	for (;!(d->base_addr->status&DRQ);); // wait for the data to be ready
	// read the data (256*16bits = 512 bytes, read as 256 shorts)
	unsigned char counter;
	for (counter=0;counter<256;counter++) {
		((short*)d->buffer)[counter] = d->base_addr->dataPort;
	}
	waitReady(d);
	d->buffered_sector = lba;
	*data = d->buffer;
	return 0;
}

int MM_IDE_writeSector(MM_IDE_DISK* d, unsigned int lba, unsigned char* data) {
	waitReady(d);
	d->base_addr->sectorCount = 1; // only write 1 sector
	writeLBA(d, lba);
	d->base_addr->command = 0x30; // send `write w/ retry` command
	for (;!(d->base_addr->status&DRQ);); // wait for the data to be ready
	// write the data (256*16bits = 512 bytes, read as 256 shorts)
	unsigned char counter;
	for (counter=0;counter<256;counter++) {
		d->base_addr->dataPort = ((short*)data)[counter];
	}
	waitReady(d);
	return 0;
}

int MM_IDE_flushSector(MM_IDE_DISK* d) {
	MM_IDE_writeSector(d, d->buffered_sector, d->buffer);
	return 0;
}
