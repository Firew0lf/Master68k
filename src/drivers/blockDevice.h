#ifndef BLOCKDEVICE_H
#define BLOCKDEVICE_H

/***
Block device structure
@struct BLOCK_DEVICE
@field blockSize size in bytes of the blocks returned by readSector
	@type unsigned int
@field devStruct pointer to the device structure provided by the driver and passed as first parameter for most functions
	@type void*
@field readSector
	@type unsigned char*(void*, unsigned int)
	@see BLOCK_DEVICE.readSector
*/

typedef struct {
	unsigned int blockSize; // size in bytes of the blocks returned by readSector
	void* devStruct; // structure provided by the device driver
	int (*readSector)(void*,unsigned int,unsigned char**);
	int (*writeSector)(void*,unsigned int,unsigned char*);
	int (*sync)(void*);
	int (*eject)(void*);
} BLOCK_DEVICE;

/***
Returns the device's postfix
*/
int registerBlockDevice(BLOCK_DEVICE* dev, char* prefix);

#endif
