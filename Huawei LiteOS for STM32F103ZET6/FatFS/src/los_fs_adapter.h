#ifndef __LOS_FS_ADAPTER_H
#define __LOS_FS_ADAPTER_H

/* Includes ------------------------------------------------------------------*/
#include <stddef.h>
#include "stdint.h"
#include "diskio.h"
#include "ff.h"
#include "los_fs.h"


/*---------------------------------------------------------------------------*/
/* Fs application interface */

int los_fopen (const char * path, unsigned char mode); /* Open or create a file */

LOS_FRESULT los_fclose (int fd); /* Close an open file object */

size_t los_fread (void* buffer, size_t size, size_t count,int fd); /* Read data from a file */

size_t los_fwrite(const void* buffer, size_t size, size_t count, int fd); /* Write data to a file */

LOS_FRESULT los_fseek( int fd, long offset); /* Move file pointer of a file object */

LOS_FRESULT los_fsync (int fd); /* Flush cached data of a writing file */

LOS_FRESULT los_fmount (const char* path, unsigned char opt); /* Mount/Unmount a logical drive */

LOS_FRESULT los_fmkfs (const char* path, unsigned char sfd, unsigned int au); /* Create a file system on the volume */


#endif /* __LOS_FS_ADAPTER_H */

