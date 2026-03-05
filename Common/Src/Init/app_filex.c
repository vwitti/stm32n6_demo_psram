/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_filex.c
  * @author  MCD Application Team
  * @brief   FileX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "tcsglobal/asg_evo.h"
#include "Common/Inc/Init/app_filex.h"
#include "Common/Inc/Init/error_handler.h"
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Message content*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
FX_MEDIA        tcs_romfs_disk;
FX_MEDIA        ps_ramfs_disk;
ALIGN_32BYTES (uint32_t fx_tcs_romfs_media_memory[FX_SRAM_DISK_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);
ALIGN_32BYTES (uint32_t fx_ps_ramfs_media_memory[FX_SRAM_DISK_DEFAULT_SECTOR_SIZE / sizeof(uint32_t)]);

#define FX_MAX_BYTE_READ 512

FX_MEDIA *  MX_FileX_GetMedia_TcsRomDisk(void)
{
	return &tcs_romfs_disk;
}

FX_MEDIA *  MX_FileX_GetMedia_RamDisk(void)
{
	return &ps_ramfs_disk;
}

#if defined (PROG_TYPE_FSBL)

UINT MX_FileX_Init_ROM_DISK(VOID *memory_ptr)
{
	UINT ret = FX_SUCCESS;

  /* Open the TCS_ROMFS disk driver */
  ret =  fx_media_open(&tcs_romfs_disk, "TCS_ROMFS", fx_stm32_xspi_direct, (VOID *)FX_NULL, (VOID *) fx_tcs_romfs_media_memory, sizeof(fx_tcs_romfs_media_memory));
  /* Check the media open sd_status */
  if (ret != FX_SUCCESS)
  {
	printf("Cant open TCS-ROMFS media driver\n");
  }

  return ret;
}

UINT MX_FileX_Init_PSRAM_DISK_MM(VOID *memory_ptr)
{
	UINT ret = FX_SUCCESS;

	  /* Format the SRAM3_BASE memory as FAT */
	  ret =  fx_media_format(&ps_ramfs_disk,                               // RamDisk pointer
			  fx_stm32_psram_memmapped,                         // Driver entry
	                            (VOID *)FX_NULL,                              // Device info pointer
	                            (UCHAR *) fx_ps_ramfs_media_memory,           // Media buffer pointer
	                            512,                                          // Media buffer size
	                            "STM32_SRAM_DISK",                            // Volume Name
	                            1,                                            // Number of FATs
	                            32,                                           // Directory Entries
	                            0,                                            // Hidden sectors
								FX_PSRAM_DISK_SIZE / FX_SRAM_DISK_DEFAULT_SECTOR_SIZE,      // Total sectors
								FX_SRAM_DISK_DEFAULT_SECTOR_SIZE,                          // Sector size
	                            4,                                            // Sectors per cluster
	                            1,                                            // Heads
	                            1);                                           // Sectors per track

	  /* Check the format status */
	  if (ret != FX_SUCCESS)
	  {
		  printf("Cant format PS-RAMFS media driver\n");
	  }

  /* Open the TCS_ROMFS disk driver */
  ret =  fx_media_open(&ps_ramfs_disk, "PS_RAMFS", fx_stm32_psram_memmapped, (VOID *)FX_NULL, (VOID *) fx_ps_ramfs_media_memory, sizeof(fx_ps_ramfs_media_memory));
  /* Check the media open sd_status */
  if (ret != FX_SUCCESS)
  {
	printf("Cant open PS-RAMFS media driver\n");
  }

  return ret;
}

#endif

#if defined (PROG_TYPE_APPLI)

UINT MX_FileX_Init_ROM_DISK_MM(VOID *memory_ptr)
{
	UINT ret = FX_SUCCESS;

  /* Open the TCS_ROMFS disk driver */
  ret =  fx_media_open(&tcs_romfs_disk, "TCS_ROMFS", fx_stm32_xspi_memmapped, (VOID *)FX_NULL, (VOID *) fx_tcs_romfs_media_memory, sizeof(fx_tcs_romfs_media_memory));
  /* Check the media open sd_status */
  if (ret != FX_SUCCESS)
  {
	printf("Cant open TCS-ROMFS media driver\n");
  }

  return ret;
}

UINT MX_FileX_Init_PSRAM_DISK_MM(VOID *memory_ptr)
{
	UINT ret = FX_SUCCESS;

	  /* Format the SRAM3_BASE memory as FAT */
	  ret =  fx_media_format(&ps_ramfs_disk,                               // RamDisk pointer
			  fx_stm32_psram_memmapped,                         // Driver entry
	                            (VOID *)FX_NULL,                              // Device info pointer
	                            (UCHAR *) fx_ps_ramfs_media_memory,           // Media buffer pointer
	                            512,                                          // Media buffer size
	                            "STM32_SRAM_DISK",                            // Volume Name
	                            1,                                            // Number of FATs
	                            32,                                           // Directory Entries
	                            0,                                            // Hidden sectors
								FX_PSRAM_DISK_SIZE / FX_SRAM_DISK_DEFAULT_SECTOR_SIZE,      // Total sectors
								FX_SRAM_DISK_DEFAULT_SECTOR_SIZE,                          // Sector size
	                            4,                                            // Sectors per cluster
	                            1,                                            // Heads
	                            1);                                           // Sectors per track

	  /* Check the format status */
	  if (ret != FX_SUCCESS)
	  {
		  printf("Cant format PS-RAMFS media driver\n");
	  }

  /* Open the TCS_ROMFS disk driver */
  ret =  fx_media_open(&ps_ramfs_disk, "PS_RAMFS", fx_stm32_psram_memmapped, (VOID *)FX_NULL, (VOID *) fx_ps_ramfs_media_memory, sizeof(fx_ps_ramfs_media_memory));
  /* Check the media open sd_status */
  if (ret != FX_SUCCESS)
  {
	printf("Cant open PS-RAMFS media driver\n");
  }

  return ret;
}

#endif

// Chad
/**
 * @brief  Read entire FileX file into a buffer.
 *
 * @param  media          Pointer to an opened FX_MEDIA
 * @param  filename       Name of the file to read
 * @param  buffer         Destination buffer
 * @param  buffer_size    Size of buffer in bytes
 * @param  out_file_size  Returns number of bytes actually read
 *
 * @return FX_SUCCESS on success, otherwise FileX error code
 */
UINT MX_Filex_read_to_buffer(CHAR *path, UCHAR *buffer, ULONG buffer_size, ULONG *out_file_size)
{
    FX_FILE file;
    UINT status;
    ULONG file_size;
    ULONG to_read;
    ULONG total_read = 0;
    ULONG actual_read;
    FX_MEDIA *media;
    char filename[FILEX_FILENAME_SIZE];
    teStatus eStatus;

    eStatus = MX_FileX_Eval_Path(path, &media, filename, sizeof(filename));
    if(eStatus != eStSuccess)
    {
    	return FX_NOT_FOUND;
    }

    if (!path || !buffer || !out_file_size)
        return FX_PTR_ERROR;


    /* Open file for reading */
    status = fx_file_open(media, &file, filename, FX_OPEN_FOR_READ);
    if (status != FX_SUCCESS)
        return status;


     file_size = file.fx_file_current_file_size;
    //printf("Size = %lu bytes\n", file_size);

    /* Get file size */
    status = fx_file_seek(&file, 0);
    if (status != FX_SUCCESS)
    {
        fx_file_close(&file);
        return status;
    }

    /* Check buffer is large enough */
    if (file_size > buffer_size)
    {
        fx_file_close(&file);
        return FX_NO_MORE_SPACE;   /* or your custom error */
    }

    /* Read file chunk by chunk */
    while (total_read < file_size)
    {
        to_read = file_size - total_read;
        if (to_read > FX_MAX_BYTE_READ)
            to_read = FX_MAX_BYTE_READ;

        status = fx_file_read(&file, buffer + total_read, to_read, &actual_read);
        if (status != FX_SUCCESS)
        {
            fx_file_close(&file);
            return status;
        }

        total_read += actual_read;

        if (actual_read == 0)
            break; // end of file
    }

    *out_file_size = total_read;

    /* Close file */
    fx_file_close(&file);

    return FX_SUCCESS;
}

UINT MX_Filex_Get_Size(CHAR *path, ULONG * file_size)
{
	UINT ret;
	FX_FILE file;
    FX_MEDIA *media;
    char filename[FILEX_FILENAME_SIZE];
    teStatus eStatus;

    if (!path || !file_size)
        return FX_PTR_ERROR;

    //printf("MX_Filex_Get_Size: %s\n", path);

    eStatus = MX_FileX_Eval_Path(path, &media, filename, sizeof(filename));
    if(eStatus != eStSuccess)
    {
    	return FX_NOT_FOUND;
    }

    /* Open file for reading */
    *file_size=0;
    ret = fx_file_open(media, &file, filename, FX_OPEN_FOR_READ);
    if (ret != FX_SUCCESS)
    {
    	printf("MX_Filex_Get_Size: %s not found\n", filename);
    	return ret;
    }

    * file_size = file.fx_file_current_file_size;
    //printf("FileX: %s Size = %lu bytes\n", filename, *file_size);

    ret = fx_file_close(&file);
    if (ret != FX_SUCCESS)
    {
    	printf("MX_Filex_Get_Size: Cannot close %s\n", filename);
    }
    return FX_SUCCESS;
}

// path: e.g. /mmc/file.txt or somepath/somefile.txt
// media: media pointer of filesystem
// filename: filename without mountpath, e.g. file.txt if path is /mmc/file.txt (only if pointer is not NULL)
// if path matches to an invalid mountpount or does not start with a '/' an error is returned
teStatus MX_FileX_Eval_Path(const char * path, FX_MEDIA ** media, char * filename, size_t filename_size)
{
	char mountpath[PATH_MOUNT_MAX+1];
	int pathcnt=0;
	int i;

	if(!path || !media)
	{
		return eStNullPointer;
	}

	if (path[pathcnt] !='/')
	{
		return eStFileNoResource;
	}

	/* Get path mount descriptor */
	pathcnt=1;
	memset(mountpath, 0x00, sizeof(mountpath));
	for(i = 0; i < PATH_MOUNT_MAX ; i++)
	{
		char c = path[i + pathcnt];

		if ( (c == 0x00) || (c == '/')) // terminating characters
		{
			break;
		}
		mountpath[i] = c;
	}
	pathcnt += i+1;



	if(!strcmp(mountpath,PATH_TCSROMFS))
	{
		*media = MX_FileX_GetMedia_TcsRomDisk();
	}
	else if(!strcmp(mountpath,PATH_MMC))
	{
		*media = MX_FileX_GetMedia_MassStorage();
	}
	else if(!strcmp(mountpath,PATH_RAMDISK))
	{
		*media = MX_FileX_GetMedia_RamDisk();
	}
	else if(!strcmp(mountpath,PATH_USB))
	{
		*media = 0; //MX_FileX_GetMedia_USBDisk();
	}
	else
	{
		*media = NULL;
		return eStFileNoResource;
	}
	if(filename != NULL)
	{
		snprintf(filename, filename_size, "%s", &path[pathcnt]);
	}

	return eStSuccess;

}

FX_MEDIA * MX_FileX_Get_Media(const char * path)
{
	FX_MEDIA * media;
	teStatus eStatus;

	//printf("MX_FileX_Get_Media: %s\n", path);
	eStatus = MX_FileX_Eval_Path(path, &media, NULL, 0);
	if(eStatus == eStSuccess)
	{
		return media;
	}
	return NULL;
}
