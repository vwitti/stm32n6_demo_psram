/*
 * asg_evo.h
 *
 *  Created on: Nov 5, 2025
 *      Author: vw
 */

#ifndef TCSGLOBAL_SYSTEM_UPDATE_H_
#define TCSGLOBAL_SYSTEM_UPDATE_H_

#ifdef __cplusplus
extern "C" {
#endif

// Key in update_list file
#define UPDATE_LIST_KEY_FSBL_BIN			"FSBL_BIN"
#define UPDATE_LIST_KEY_FSBL_HEADER			"FSBL_HEADER"
#define UPDATE_LIST_KEY_APPLI_BIN			"APPLI_BIN"
#define UPDATE_LIST_KEY_APPLI_HEADER		"APPLI_HEADER"
#define UPDATE_LIST_KEY_TCS_ROMFS_BIN       "TCS_ROMFS_BIN"
#define UPDATE_LIST_KEY_TCS_ROMFS_HEADER    "TCS_ROMFS_HEADER"
#define UPDATE_LIST_KEY_TOUCHGFX_ASSETS_BIN "TOUCHGFX_ASSETS_BIN"
#define UPDATE_LIST_KEY_TOUCHGFX_ASSETS_CRC "TOUCHGFX_ASSETS_CRC"


#define TCS_ROMFS_HEADER_SIZE				(9)					// 8 Byte CRC Sum
#define TOUCHGFX_ASSETS_CRC_SIZE			(9)					// 8 Byte CRC Sum

// Offset & Size in XSPI flash
#define XSPI_TRUSTED_HEADER_SIZE			(0x400)				// 1kByte Header with trusted information on FSBL or APPLI
#define XSPI_UPDATE_ERASE_BLOCK_SIZE		(0x10000)			// Maximum erase block size of SPI flash use for update process due to speed
#define XSPI_UPDATE_PAGEPROG_BLOCK_SIZE		(0x100)				// Maximum page block size of SPI flash use for update process, see 10-28 RM mxuw66
#define XSPI_UPDATE_ERASE_BLOCK_SIZE_IN_KB	(XSPI_UPDATE_ERASE_BLOCK_SIZE >> 10)

/* NOTE: */
/* ------------------------------------------------- */
/* This settings MUST BE IN SYNC together            */
/* tcs/tcsglocal/system_constants.h                  */
/* BSP/<Board>/BSP/Appli/STM32N657XX_XIP.ld          */
/* BSP/<Board>/BSP/FSBL/STM32N657XX_AXISRAM2_fsbl.ld */
/* ------------------------------------------------- */
#define XSPI_OFFSET_FSBL					(0x00000000)		// Base address XSPI memory mapped 0x70000000 (by STM32N6 Hardware)
#define XSPI_OFFSET_FSBL_ASSETS				(0x0004D000)		// Base address XSPI memory mapped 0x7004D000
#define XSPI_OFFSET_APPLI					(0x00100000)		// Base address XSPI memory mapped 0x70100000 (by ST EXTMEM Manager)
#define XSPI_OFFSET_TOUCHGFX_ASSETS         (0x00900000)		// Base address XSPI memory mapped 0x70200000 (by linker command file)

// see tcs/romfs. ROMFS is created by create_tcs_romfs.sh as a 4 MB FAT16 disk. The ROMFS is mapped at the end of memory area
#define XSPI_OFFSET_TCS_ROMFS				(0x07C00000)		// Base address XSPI memory mapped 0x7C000000
#define XSPI_SIZE_TCS_ROMFS					(0x00400000)		// Size of area for TCS-ROMFS in XSPI memory

// Max Sizes of images in flash (Limits number of sector to be erased)
#define UPDATE_MAX_SIZE_FSBL				(0x100000)			// Could be up to 1 MByte
#define UPDATE_MAX_SIZE_APPLI				(0x800000)			// Exact definition, see linker command file
#define UPDATE_MAX_SIZE_TCSROMFS			(0x400000)			// Exact definition, see linker command file
#define UPDATE_MAX_SIZE_TOUCHGFX_ASSETS     (0xC00000)			// Exact definition, see linker command file

#define XSPI_FLASH_PHY_ADDR(x)				(XSPI2_BASE + (x))

#define DISCORVERY_GRAPHIC_LIB_INSTANCE		(0)

#ifdef __cplusplus
}
#endif

#endif /* TCSGLOBAL_SYSTEM_UPDATE_H_ */
