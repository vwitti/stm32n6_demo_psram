/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "tcsglobal/asg_evo.h"
#include "tcsglobal/status_codes.h"
#include "tcsglobal/system_constants.h"
#include "fx_api.h"
#include "BSP/Inc/xspi.h"
#include "Utils/kv_store.h"
#include "Utils/printf_utils.h"
#include "Common/Inc/Init/app_netxduo.h"
#include "Common/Inc/Init/app_filex.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Update/firmware_update.h"
#include "Common/Inc/Init/extmem/extmem_manager.h"

/* Private includes ----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static kv_store_t update_list;
static uint8_t trusted_header[XSPI_TRUSTED_HEADER_SIZE];
static uint8_t trusted_header_xspi[XSPI_TRUSTED_HEADER_SIZE];
static uint8_t program_buffer[XSPI_UPDATE_PAGEPROG_BLOCK_SIZE];

teStatus Update_Check_FSBL_Bootloader(bool * is_update_needed)
{
	teStatus ret;
	ULONG out_file_size;
	const char * item;
	char path[FILEX_FILENAME_SIZE];

	if(is_update_needed == NULL)
	{
		return eStNullPointer;
	}
	*is_update_needed = false;
	printf("Update FSBL: read and download trusted header\n");

	item = kv_get(&update_list, UPDATE_LIST_KEY_FSBL_HEADER);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_FSBL_HEADER);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	MX_NetXDuo_Init_FTP_DownloadFile(item);

	/* Read trusted header to RAM and compare */
	snprintf(path, sizeof(path), "/%s/%s", FTP_DOWNLOAD_PATH, item);
	ret = MX_Filex_read_to_buffer((CHAR *)path, trusted_header, sizeof(trusted_header), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		printf("Cant read header: %d\n", ret);
		return eStFileCantRead;
	}
	//print_hex(trusted_header, sizeof(trusted_header), 16);

	/* Read trusted Header from flash */
	EXTMEM_StatusTypeDef ret_extmem = EXTMEM_Read(EXTMEM_SPI_FLASH, XSPI_OFFSET_FSBL, (uint8_t *)trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE);
	if(ret_extmem != EXTMEM_OK)
	{
		printf("EXTMEM: cannot read trusted header: %d\n", ret_extmem);
		return eStHwDevCantReceive;
	}
	//print_hex((const uint8_t *)trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE, 16);
	int res_memcmp = memcmp(trusted_header, trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE);
	if(res_memcmp != 0)
	{
		* is_update_needed = true;
	}
	return eStSuccess;
}

teStatus Update_FSBL_Bootloader(void)
{
	const char * item;
	ULONG file_size;
	ULONG num_erase_blocks;
	ULONG num_prog_blocks;
	UINT ret;
	teStatus eStatus;
	EXTMEM_StatusTypeDef ret_extmem;
	uint32_t addr;
	ULONG iter;
	char filename[FILEX_FILENAME_SIZE];

	item = kv_get(&update_list, UPDATE_LIST_KEY_FSBL_BIN);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_FSBL_BIN);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	StartScreenLcd_WriteLine("Update: FSBL (Do not power off!)");
	ret = MX_NetXDuo_Init_FTP_DownloadFile(item);
	if (ret != FX_SUCCESS)
	{
		printf("Cannot download FSBL image %s from server.\n", item);
		return eStFileNotFound;
	}

	// Retrieve size of file to determine number of erase blocks
	snprintf(filename, sizeof(filename), "%s%s%s%s", PATH_SEPARATOR, FTP_DOWNLOAD_PATH, PATH_SEPARATOR, item);
	MX_Filex_Get_Size( (CHAR*)filename, &file_size);
	if(file_size > UPDATE_MAX_SIZE_FSBL)
	{
		printf("Update: FSBL %s too large (%ld)\n", item, file_size);
		return eStSizeTooLarge;
	}

	//////////////////////////////////// ERASE ///////////////////////////////////
	num_erase_blocks = (file_size + XSPI_UPDATE_ERASE_BLOCK_SIZE) / XSPI_UPDATE_ERASE_BLOCK_SIZE;
	printf("Update FSBL: %s size is %ld bytes\n", item, file_size);
	printf("Update FSBL: and needs %ld %dkB erase blocks\n", num_erase_blocks, XSPI_UPDATE_ERASE_BLOCK_SIZE_IN_KB);

	eStatus = eStSuccess;
	for(iter = 0; iter < num_erase_blocks; iter++)
	{
		addr = XSPI_OFFSET_FSBL + (iter * XSPI_UPDATE_ERASE_BLOCK_SIZE);

		printf("XSPI: erase flash block: (%ld of %ld) Addr=%08lX\r", iter + 1, num_erase_blocks, addr);
		ret_extmem = EXTMEM_EraseSector(EXTMEM_SPI_FLASH, addr, XSPI_UPDATE_ERASE_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantErase;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot erase flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		return eStatus;
	}

	//////////////////////////////////// PROGRAM ///////////////////////////////////
	num_prog_blocks = (file_size + XSPI_UPDATE_PAGEPROG_BLOCK_SIZE) / XSPI_UPDATE_PAGEPROG_BLOCK_SIZE;
	printf("Update FSBL: %s needs %ld program page blocks\n", item, num_prog_blocks);

	FX_FILE  file;
	ret = fx_file_open(MX_File_FtpDownload(), &file, (CHAR*)item, FX_OPEN_FOR_READ);
	if (ret != FX_SUCCESS)
	{
		printf("FileX: Cant open file %s, error: %u\n", item, ret);
		return eStFileCantOpen;
	}
	/* Dateizeiger auf Anfang setzen (optional, aber sauber) */
	fx_file_seek(&file, 0);

	eStatus = eStSuccess;
	ULONG bytes_read_from_file;
	for(iter = 0; iter < num_prog_blocks; iter++)
	{
		/* Read program page chunk from file */
		ret = fx_file_read(&file, program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE, &bytes_read_from_file);
		if (ret == FX_END_OF_FILE)
		{
			printf("\nFileX: EOF reached %s, last_byte: %lu\n", item, bytes_read_from_file);
		}
		else if (ret != FX_SUCCESS)
		{
			printf("\nFileX: Cant read file %s, error: %u\n", item, ret);
			eStatus = eStFileCantRead;
			break;
		}

		addr = XSPI_OFFSET_FSBL + (iter * XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);

		printf("XSPI: program page block: (%ld of %ld) Addr=%08lX\r", iter + 1 , num_prog_blocks, addr);
		ret_extmem = EXTMEM_Write(EXTMEM_SPI_FLASH, addr, (uint8_t *)program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantProgram;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot program flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		//return eStatus;
	}

	/* Datei schließen (wichtig!) */
	fx_file_close(&file);

	return eStatus;
}

teStatus Update_Check_FSBL_Application(bool * is_update_needed)
{
	teStatus ret;
	ULONG out_file_size;
	const char * item;
	char path[FILEX_FILENAME_SIZE];

	if(is_update_needed == NULL)
	{
		return eStNullPointer;
	}
	*is_update_needed = false;
	printf("Update APPLI: read and download trusted header\n");

	item = kv_get(&update_list, UPDATE_LIST_KEY_APPLI_HEADER);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_APPLI_HEADER);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	MX_NetXDuo_Init_FTP_DownloadFile(item);

	/* Read trusted header to RAM and compare */
	snprintf(path, sizeof(path), "/%s/%s", FTP_DOWNLOAD_PATH, item);
	ret = MX_Filex_read_to_buffer((CHAR *)path, trusted_header, sizeof(trusted_header), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		printf("Cant read header: %d\n", ret);
		return eStFileCantRead;
	}
	//print_hex(trusted_header, sizeof(trusted_header), 16);

	/* Read trusted Header from flash */
	EXTMEM_StatusTypeDef ret_extmem = EXTMEM_Read(EXTMEM_SPI_FLASH, XSPI_OFFSET_APPLI, (uint8_t *)trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE);
	if(ret_extmem != EXTMEM_OK)
	{
		printf("EXTMEM: cannot read trusted header: %d\n", ret_extmem);
		return eStHwDevCantReceive;
	}

	//print_hex((const uint8_t *)trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE, 16);
	int res_memcmp = memcmp(trusted_header, trusted_header_xspi, XSPI_TRUSTED_HEADER_SIZE);
	if(res_memcmp != 0)
	{
		* is_update_needed = true;
	}
	return eStSuccess;
}

teStatus Update_APPLI_Application(void)
{
	const char * item;
	ULONG file_size;
	ULONG num_erase_blocks;
	ULONG num_prog_blocks;
	UINT ret;
	teStatus eStatus;
	EXTMEM_StatusTypeDef ret_extmem;
	uint32_t addr;
	ULONG iter;
	char filename[FILEX_FILENAME_SIZE];

	item = kv_get(&update_list, UPDATE_LIST_KEY_APPLI_BIN);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_APPLI_BIN);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	StartScreenLcd_WriteLine("Update: APPLI (Do not power off!)");
	ret = MX_NetXDuo_Init_FTP_DownloadFile(item);
	if (ret != FX_SUCCESS)
	{
		printf("Cannot download APPLI image %s from server.\n", item);
		return eStFileNotFound;
	}

	// Retrieve size of file to determine number of erase blocks
	snprintf(filename, sizeof(filename), "%s%s%s%s", PATH_SEPARATOR, FTP_DOWNLOAD_PATH, PATH_SEPARATOR, item);
	MX_Filex_Get_Size( (CHAR*)filename, &file_size);
	if(file_size > UPDATE_MAX_SIZE_APPLI)
	{
		printf("Update: APPLI %s too large (%ld)\n", item, file_size);
		return eStSizeTooLarge;
	}

	//////////////////////////////////// ERASE ///////////////////////////////////
	num_erase_blocks = (file_size + XSPI_UPDATE_ERASE_BLOCK_SIZE) / XSPI_UPDATE_ERASE_BLOCK_SIZE;
	printf("Update APPLI: %s size is %ld bytes\n", item, file_size);
	printf("Update APPLI: and needs %ld %dkB erase blocks\n", num_erase_blocks, XSPI_UPDATE_ERASE_BLOCK_SIZE_IN_KB);

	eStatus = eStSuccess;
	for(iter = 0; iter < num_erase_blocks; iter++)
	{
		addr = XSPI_OFFSET_APPLI + (iter * XSPI_UPDATE_ERASE_BLOCK_SIZE);

		printf("XSPI: erase flash block: (%ld of %ld) Addr=%08lX\r", iter + 1, num_erase_blocks, addr);
		ret_extmem = EXTMEM_EraseSector(EXTMEM_SPI_FLASH, addr, XSPI_UPDATE_ERASE_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantErase;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot erase flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		return eStatus;
	}

	//////////////////////////////////// PROGRAM ///////////////////////////////////
	num_prog_blocks = (file_size + XSPI_UPDATE_PAGEPROG_BLOCK_SIZE) / XSPI_UPDATE_PAGEPROG_BLOCK_SIZE;
	printf("Update APPLI: %s needs %ld program page blocks\n", item, num_prog_blocks);

	FX_FILE  file;
	ret = fx_file_open(MX_File_FtpDownload(), &file, (CHAR*)item, FX_OPEN_FOR_READ);
	if (ret != FX_SUCCESS)
	{
		printf("FileX: Cant open file %s, error: %u\n", item, ret);
		return eStFileCantOpen;
	}
	/* Dateizeiger auf Anfang setzen (optional, aber sauber) */
	fx_file_seek(&file, 0);

	eStatus = eStSuccess;
	ULONG bytes_read_from_file;
	for(iter = 0; iter < num_prog_blocks; iter++)
	{
		/* Read program page chunk from file */
		ret = fx_file_read(&file, program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE, &bytes_read_from_file);
		if (ret == FX_END_OF_FILE)
		{
			printf("\nFileX: EOF reached %s, last_byte: %lu\n", item, bytes_read_from_file);
		}
		else if (ret != FX_SUCCESS)
		{
			printf("\nFileX: Cant read file %s, error: %u\n", item, ret);
			eStatus = eStFileCantRead;
			break;
		}

		addr = XSPI_OFFSET_APPLI + (iter * XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);

		printf("XSPI: program page block: (%ld of %ld) Addr=%08lX\r", iter + 1 , num_prog_blocks, addr);
		ret_extmem = EXTMEM_Write(EXTMEM_SPI_FLASH, addr, (uint8_t *)program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantProgram;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot program flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		//return eStatus;
	}

	/* Datei schließen (wichtig!) */
	fx_file_close(&file);

	return eStatus;
}

teStatus Update_Check_TCSROMFS(bool * is_update_needed)
{
	teStatus ret;
	ULONG out_file_size;
	const char * item;
	char path[FILEX_FILENAME_SIZE];
	unsigned char crc32_download[TCS_ROMFS_HEADER_SIZE];
	unsigned char crc32_file[TCS_ROMFS_HEADER_SIZE];

	memset(crc32_download, 0x00, sizeof(crc32_download));
	memset(crc32_file, 0x00, sizeof(crc32_file));

	if(is_update_needed == NULL)
	{
		return eStNullPointer;
	}
	*is_update_needed = false;
	printf("Update TCSROMFS: read and download crc header\n");

	item = kv_get(&update_list, UPDATE_LIST_KEY_TCS_ROMFS_HEADER);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_TCS_ROMFS_HEADER);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	MX_NetXDuo_Init_FTP_DownloadFile(item);

	/* Read trusted header to RAM and compare */
	snprintf(path, sizeof(path), "/%s/%s", FTP_DOWNLOAD_PATH, item);

	ret = MX_Filex_read_to_buffer((CHAR *)path, crc32_download, sizeof(crc32_download), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		printf("Cant read header: %d\n", ret);
		return eStFileCantRead;
	}
	//printf("TCS ROMFS DOWNLOAD\n");
	//print_hex(crc32_download, sizeof(crc32_download), 8);

	/* Read CRC from flash */
	ret = MX_Filex_read_to_buffer(PATH_FILE_TCSROM_FS_CRC32, crc32_file, sizeof(crc32_file), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		/* If this file is not present, update ROM FS, e.g. no ROMFS before update */
		printf("Cant read ROM CRC file: %d\n", ret);
		* is_update_needed = true;
		return eStSuccess;
	}
	//printf("TCS ROMFS FLASH\n");
	//print_hex(crc32_file, sizeof(crc32_file), 8);

	int res_memcmp = memcmp(crc32_download, crc32_file, TCS_ROMFS_HEADER_SIZE);
	if(res_memcmp != 0)
	{
		* is_update_needed = true;
	}
	return eStSuccess;
}

teStatus Update_TCSROMFS(void)
{
	const char * item;
	ULONG file_size;
	ULONG num_erase_blocks;
	ULONG num_prog_blocks;
	UINT ret;
	teStatus eStatus;
	EXTMEM_StatusTypeDef ret_extmem;
	uint32_t addr;
	ULONG iter;
	char filename[FILEX_FILENAME_SIZE];

	item = kv_get(&update_list, UPDATE_LIST_KEY_TCS_ROMFS_BIN);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_TCS_ROMFS_BIN);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	StartScreenLcd_WriteLine("Update: TCSROMFS (Do not power off!)");
	ret = MX_NetXDuo_Init_FTP_DownloadFile(item);
	if (ret != FX_SUCCESS)
	{
		printf("Cannot download TCSROMFS image %s from server.\n", item);
		return eStFileNotFound;
	}

	// Retrieve size of file to determine number of erase blocks
	snprintf(filename, sizeof(filename), "%s%s%s%s", PATH_SEPARATOR, FTP_DOWNLOAD_PATH, PATH_SEPARATOR, item);
	MX_Filex_Get_Size( (CHAR*)filename, &file_size);
	if(file_size > UPDATE_MAX_SIZE_TCSROMFS)
	{
		printf("Update: TCSROMFS %s too large (%ld)\n", item, file_size);
		return eStSizeTooLarge;
	}

	//////////////////////////////////// ERASE ///////////////////////////////////
	num_erase_blocks = (file_size + XSPI_UPDATE_ERASE_BLOCK_SIZE) / XSPI_UPDATE_ERASE_BLOCK_SIZE;
	printf("Update TCSROMFS: %s size is %ld bytes\n", item, file_size);
	printf("Update TCSROMFS: and needs %ld %dkB erase blocks\n", num_erase_blocks, XSPI_UPDATE_ERASE_BLOCK_SIZE_IN_KB);

	eStatus = eStSuccess;
	for(iter = 0; iter < num_erase_blocks; iter++)
	{
		addr = XSPI_OFFSET_TCS_ROMFS + (iter * XSPI_UPDATE_ERASE_BLOCK_SIZE);

		printf("XSPI: erase flash block: (%ld of %ld) Addr=%08lX\r", iter + 1, num_erase_blocks, addr);
		ret_extmem = EXTMEM_EraseSector(EXTMEM_SPI_FLASH, addr, XSPI_UPDATE_ERASE_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantErase;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot erase flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		return eStatus;
	}

	//////////////////////////////////// PROGRAM ///////////////////////////////////
	num_prog_blocks = (file_size + XSPI_UPDATE_PAGEPROG_BLOCK_SIZE) / XSPI_UPDATE_PAGEPROG_BLOCK_SIZE;
	printf("Update TCSROMFS: %s needs %ld program page blocks\n", item, num_prog_blocks);

	FX_FILE  file;
	ret = fx_file_open(MX_File_FtpDownload(), &file, (CHAR*)item, FX_OPEN_FOR_READ);
	if (ret != FX_SUCCESS)
	{
		printf("FileX: Cant open file %s, error: %u\n", item, ret);
		return eStFileCantOpen;
	}
	/* Dateizeiger auf Anfang setzen (optional, aber sauber) */
	fx_file_seek(&file, 0);

	eStatus = eStSuccess;
	ULONG bytes_read_from_file;
	for(iter = 0; iter < num_prog_blocks; iter++)
	{
		/* Read program page chunk from file */
		ret = fx_file_read(&file, program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE, &bytes_read_from_file);
		if (ret == FX_END_OF_FILE)
		{
			printf("\nFileX: EOF reached %s, last_byte: %lu\n", item, bytes_read_from_file);
		}
		else if (ret != FX_SUCCESS)
		{
			printf("\nFileX: Cant read file %s, error: %u\n", item, ret);
			eStatus = eStFileCantRead;
			break;
		}

		addr = XSPI_OFFSET_TCS_ROMFS + (iter * XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);

		printf("XSPI: program page block: (%ld of %ld) Addr=%08lX\r", iter + 1 , num_prog_blocks, addr);
		ret_extmem = EXTMEM_Write(EXTMEM_SPI_FLASH, addr, (uint8_t *)program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantProgram;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot program flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		//return eStatus;
	}

	/* Datei schließen (wichtig!) */
	fx_file_close(&file);

	return eStatus;
}

teStatus Update_Check_TOUCHGFX_Assets(bool * is_update_needed)
{
	teStatus ret;
	ULONG out_file_size;
	const char * item;
	char path[FILEX_FILENAME_SIZE];
	unsigned char crc32_download[TOUCHGFX_ASSETS_CRC_SIZE];
	unsigned char crc32_file[TOUCHGFX_ASSETS_CRC_SIZE];

	memset(crc32_download, 0x00, sizeof(crc32_download));
	memset(crc32_file, 0x00, sizeof(crc32_file));

	if(is_update_needed == NULL)
	{
		return eStNullPointer;
	}
	*is_update_needed = false;
	printf("Update TOUCHGFXAssets: read and download crc header\n");

	item = kv_get(&update_list, UPDATE_LIST_KEY_TOUCHGFX_ASSETS_CRC);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_TOUCHGFX_ASSETS_CRC);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	MX_NetXDuo_Init_FTP_DownloadFile(item);

	/* Read trusted header to RAM and compare */
	snprintf(path, sizeof(path), "/%s/%s", FTP_DOWNLOAD_PATH, item);

	ret = MX_Filex_read_to_buffer((CHAR *)path, crc32_download, sizeof(crc32_download), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		printf("Cant read header: %d\n", ret);
		return eStFileCantRead;
	}
	//print_hex(crc32_download, sizeof(crc32_download), 8);

	/* Read CRC from flash */
	ret = MX_Filex_read_to_buffer(PATH_FILE_TOUCHGFX_CRC32, crc32_file, sizeof(crc32_file), &out_file_size);
	if(ret != FX_SUCCESS)
	{
		/* If this file is not present, update ROM FS, e.g. no ROMFS before update */
		printf("Cant read ROM CRC file: %d\n", ret);
		* is_update_needed = true;
		return eStSuccess;
	}
	//print_hex(crc32_file, sizeof(crc32_file), 8);

	int res_memcmp = memcmp(crc32_download, crc32_file, TOUCHGFX_ASSETS_CRC_SIZE);
	if(res_memcmp != 0)
	{
		* is_update_needed = true;
	}
	return eStSuccess;
}

teStatus Update_TOUCHGFX_Assets(void)
{
	const char * item;
	ULONG file_size;
	ULONG num_erase_blocks;
	ULONG num_prog_blocks;
	UINT ret;
	teStatus eStatus;
	EXTMEM_StatusTypeDef ret_extmem;
	uint32_t addr;
	ULONG iter;
	char filename[FILEX_FILENAME_SIZE];

	item = kv_get(&update_list, UPDATE_LIST_KEY_TOUCHGFX_ASSETS_BIN);
	if(item == NULL)
	{
		/* key not found in list */
		printf("No key %s found!\n", UPDATE_LIST_KEY_TOUCHGFX_ASSETS_BIN);
		return eStNotFound;
	}

	/* Download trusted header for compare */
	StartScreenLcd_WriteLine("Update: TOUCHGFXAssets (Do not power off!)");
	ret = MX_NetXDuo_Init_FTP_DownloadFile(item);
	if (ret != FX_SUCCESS)
	{
		printf("Cannot download TOUCHGFXAssets image %s from server.\n", item);
		return eStFileNotFound;
	}

	// Retrieve size of file to determine number of erase blocks
	snprintf(filename, sizeof(filename), "%s%s%s%s", PATH_SEPARATOR, FTP_DOWNLOAD_PATH, PATH_SEPARATOR, item);
	MX_Filex_Get_Size( (CHAR*)filename, &file_size);
	if(file_size > UPDATE_MAX_SIZE_TOUCHGFX_ASSETS)
	{
		printf("Update: TOUCHGFXAssets %s too large (%ld)\n", item, file_size);
		return eStSizeTooLarge;
	}

	//////////////////////////////////// ERASE ///////////////////////////////////
	num_erase_blocks = (file_size + XSPI_UPDATE_ERASE_BLOCK_SIZE) / XSPI_UPDATE_ERASE_BLOCK_SIZE;
	printf("Update TOUCHGFXAssets: %s size is %ld bytes\n", item, file_size);
	printf("Update TOUCHGFXAssets: and needs %ld %dkB erase blocks\n", num_erase_blocks, XSPI_UPDATE_ERASE_BLOCK_SIZE_IN_KB);

	eStatus = eStSuccess;
	for(iter = 0; iter < num_erase_blocks; iter++)
	{
		addr = XSPI_OFFSET_TOUCHGFX_ASSETS + (iter * XSPI_UPDATE_ERASE_BLOCK_SIZE);

		printf("XSPI: erase flash block: (%ld of %ld) Addr=%08lX\r", iter + 1, num_erase_blocks, addr);
		ret_extmem = EXTMEM_EraseSector(EXTMEM_SPI_FLASH, addr, XSPI_UPDATE_ERASE_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantErase;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot erase flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		return eStatus;
	}

	//////////////////////////////////// PROGRAM ///////////////////////////////////
	num_prog_blocks = (file_size + XSPI_UPDATE_PAGEPROG_BLOCK_SIZE) / XSPI_UPDATE_PAGEPROG_BLOCK_SIZE;
	printf("Update TOUCHGFXAssets: %s needs %ld program page blocks\n", item, num_prog_blocks);

	FX_FILE  file;
	ret = fx_file_open(MX_File_FtpDownload(), &file, (CHAR*)item, FX_OPEN_FOR_READ);
	if (ret != FX_SUCCESS)
	{
		printf("FileX: Cant open file %s, error: %u\n", item, ret);
		return eStFileCantOpen;
	}
	/* Dateizeiger auf Anfang setzen (optional, aber sauber) */
	fx_file_seek(&file, 0);

	eStatus = eStSuccess;
	ULONG bytes_read_from_file;
	for(iter = 0; iter < num_prog_blocks; iter++)
	{
		/* Read program page chunk from file */
		ret = fx_file_read(&file, program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE, &bytes_read_from_file);
		if (ret == FX_END_OF_FILE)
		{
			printf("\nFileX: EOF reached %s, last_byte: %lu\n", item, bytes_read_from_file);
		}
		else if (ret != FX_SUCCESS)
		{
			printf("\nFileX: Cant read file %s, error: %u\n", item, ret);
			eStatus = eStFileCantRead;
			break;
		}

		addr = XSPI_OFFSET_TOUCHGFX_ASSETS + (iter * XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);

		printf("XSPI: program page block: (%ld of %ld) Addr=%08lX\r", iter + 1 , num_prog_blocks, addr);
		ret_extmem = EXTMEM_Write(EXTMEM_SPI_FLASH, addr, (uint8_t *)program_buffer, XSPI_UPDATE_PAGEPROG_BLOCK_SIZE);
		if(ret_extmem != EXTMEM_OK)
		{
			eStatus = eStHwDevCantProgram;
			break;
		}
	}
	printf("\n");
	if(eStatus != eStSuccess)
	{
		printf("XSPI: cannot program flash block %ld at %08lX (res=%d)\n", iter, addr, ret_extmem);
		//return eStatus;
	}

	/* Datei schließen (wichtig!) */
	fx_file_close(&file);

	return eStatus;
}

teStatus Update_CheckFtpServer(void)
{
	ULONG ret;

	StartScreenLcd_WriteLine("Contact FTP server %s for updates", App_NetXDuo_GetFTP_Server_Address());

	ret = MX_NetXDuo_Init_FTP_CreatOpen();
	if(ret != NX_SUCCESS)
	{
		StartScreenLcd_WriteLine("Cannot open FTP server %s !", App_NetXDuo_GetFTP_Server_Address());
		return eStNotConnected;
	}

	/* Load file with list of Update artefacts */
	ret = MX_NetXDuo_Init_FTP_DownloadFile(FILE_NAME_UPDATE_LIST);
	if(ret != NX_SUCCESS)
	{
		printf("Update: Cant download update list file %s\n", FILE_NAME_UPDATE_LIST);
		return eStNotConnected;
	}
	printf("Update: Connection to FTP server established\n");

	kv_init(&update_list);
	kv_load_from_file(&update_list, LOCAL_PATH_UPDATE_LIST);

	return eStSuccess;
}

teStatus Update_CloseFtpServer(void)
{
	UINT ret;

	ret = MX_NetXDuo_Init_FTP_Close(); /* Do not treat as error */
	if(ret != NX_SUCCESS)
	{
		printf("failure disconnect FTP server %s\n", App_NetXDuo_GetFTP_Server_Address());
	}
	// Free ressources from update list
	kv_free(&update_list);
	printf("Update: Connection to FTP server shutdown\n");
	return eStSuccess;
}

