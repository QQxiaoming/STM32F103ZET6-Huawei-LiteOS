#include "los_fs_adapter.h"


FIL fnew;    /* file objects */
FATFS fs;    /* Work area (file system object) for logical drives */
UINT br;
UINT bw;

/*******************************************************************************
* Function Name  : los_fopen
* Description    : Open or create a file
* Input          : path
                   mode
* Output         : None
* Return         : fd
*******************************************************************************/
int los_fopen (const char * path, unsigned char mode)
{
    FRESULT fResult;
    fResult = f_open (&fnew, path, (BYTE)mode);
    if(FR_OK != fResult)
    {
        return 0;
    }

    return (int)&fnew;
}

/*******************************************************************************
* Function Name  : los_fclose
* Description    : Close an open file object
* Input          : int fd
* Output         : None
* Return         : LOS_FRESULT
*******************************************************************************/
LOS_FRESULT los_fclose (int fd)
{
    return (LOS_FRESULT)f_close ((FIL *)fd);
}

/*******************************************************************************
* Function Name  : los_fread
* Description    : Read data from a file
* Input          : size_t size,
                   size_t count,
                   int fd
* Output         : void* buffer
* Return         : num of read byte
*******************************************************************************/
size_t los_fread (void* buffer, size_t size, size_t count,int fd)
{
    FRESULT fResult;

    br = 0;

    fResult = f_read ((FIL *)fd, buffer,size*count, &br);

    if(FR_OK != fResult)
    {
        return 0;
    }

    return br;
}

/*******************************************************************************
* Function Name  : los_fwrite
* Description    : Write data to a file
* Input          : const void* buffer,
                   size_t size,
                   size_t count,
                   int fd
* Output         : None
* Return         : num of write byte
*******************************************************************************/
size_t los_fwrite(const void* buffer, size_t size, size_t count, int fd)
{
    FRESULT fResult;

    bw = 0;

    fResult = f_write ((FIL *)fd, buffer, size*count,&bw);

    if(FR_OK != fResult)
    {
      return 0;
    }

    return bw;
}

/*******************************************************************************
* Function Name  : los_fseek
* Description    : Move file pointer of a file object
* Input          : long offset
* Output         : int fd
* Return         : LOS_FRESULT
*******************************************************************************/
LOS_FRESULT los_fseek( int fd, long offset)
{
    return (LOS_FRESULT)f_lseek ((FIL *)fd, offset);
}

/*******************************************************************************
* Function Name  : los_fsync
* Description    : Flush cached data of a writing file
* Input          : int fd
* Output         : None
* Return         : LOS_FRESULT
*******************************************************************************/
LOS_FRESULT los_fsync (int fd)
{
    return (LOS_FRESULT)f_sync ((FIL *)fd);
}

/*******************************************************************************
* Function Name  : los_fmount
* Description    : Mount/Unmount a logical drive
* Input          : const char* path,
                   unsigned char opt
* Output         : None
* Return         : LOS_FRESULT
*******************************************************************************/
LOS_FRESULT los_fmount (const char* path, unsigned char opt)
{
    return (LOS_FRESULT)f_mount(&fs, path, opt);
}

/*******************************************************************************
* Function Name  : los_fmkfs
* Description    : Create a file system on the volume
* Input          : const TCHAR* path,
                   unsigned char sfd,
                   unsigned int au
* Output         : None
* Return         : LOS_FRESULT
*******************************************************************************/
LOS_FRESULT los_fmkfs (const char* path, unsigned char sfd, unsigned int au)
{
    return (LOS_FRESULT)f_mkfs(path, sfd, au);
}



