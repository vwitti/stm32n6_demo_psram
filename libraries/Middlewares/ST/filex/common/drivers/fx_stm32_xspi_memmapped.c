
/**************************************************************************/
/*                                                                        */
/*       Copyright (c) Microsoft Corporation. All rights reserved.        */
/*                                                                        */
/*       This software is licensed under the Microsoft Software License   */
/*       Terms for Microsoft Azure RTOS. Full text of the license can be  */
/*       found in the LICENSE file at https://aka.ms/AzureRTOS_EULA       */
/*       and in the root directory of this software.                      */
/*                                                                        */
/**************************************************************************/


/**************************************************************************/
/**************************************************************************/
/**                                                                       */
/** FileX Component                                                       */
/**                                                                       */
/**   RAM Disk Driver                                                     */
/**                                                                       */
/**************************************************************************/
/**************************************************************************/


/* Include necessary system files.  */
#include <stdio.h>
#include "BSP/Inc/fx_stm32_xspi_memmapped_driver.h"
#include "Utils/printf_utils.h"

#if 0
static UINT is_initialized = 0;
#endif
VOID  fx_stm32_xspi_memmapped(FX_MEDIA *media_ptr)
{

UCHAR *source_buffer;
#if 0
UCHAR *destination_buffer;
#endif
UINT   bytes_per_sector;
#if 0
UCHAR *destination_buffer_end;
#endif
UCHAR *source_buffer_end;
/* Calculate SRAM disk end address */
UCHAR *sram_disk_end = ((UCHAR *)(FX_SRAM_DISK_BASE_ADDRESS + FX_SRAM_DISK_SIZE));
    /* Process the driver request specified in the media control block.  */
    switch (media_ptr->fx_media_driver_request)
    {

        case FX_DRIVER_INIT:
        {
            /*
             * the FX_DRIVER_INIT can be requested either from the fx_media_format() or fx_media_open()
             * as the RAM memory should be always formatted before being used, by memset'ing it to '\0'
             * we need to avoid double initialization to keep the file system integrity.
             */
#if 0
            if (is_initialized == 0)
            {
                _fx_utility_memory_set((UCHAR *)FX_SRAM_DISK_BASE_ADDRESS, '\0', FX_SRAM_DISK_SIZE);
                is_initialized = 1;
            }
#endif
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_UNINIT:
        {
            /* there is nothing to do for FX_DRIVER_UNINIT request
             *  set the media driver status to FX_SUCCESS.
             */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_READ:
        {

            /* Calculate the RAM disk sector offset.*/
            source_buffer = ((UCHAR *)FX_SRAM_DISK_BASE_ADDRESS) +
                             ((media_ptr->fx_media_driver_logical_sector + media_ptr->fx_media_hidden_sectors) * media_ptr->fx_media_bytes_per_sector);

            /* Calculate source buffer end address */
            source_buffer_end = source_buffer + (media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);

            /* Check source buffer does not exceed sram disk end address */
            if (source_buffer_end  > sram_disk_end)
            {
              media_ptr -> fx_media_driver_status =  FX_PTR_ERROR;
              break;
            }
            else
            {
              /* Copy the RAM sector into the destination.  */
              _fx_utility_memory_copy(source_buffer, media_ptr -> fx_media_driver_buffer,
                                       media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);
              //printf("FX_DR: %08lX %ld\n", (uint32_t) source_buffer, media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);
              //print_hex(media_ptr -> fx_media_driver_buffer, media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector, 32);
              /* Successful driver request.  */
              media_ptr->fx_media_driver_status = FX_SUCCESS;
              break;
            }
        }

        case FX_DRIVER_WRITE:
        {
        	printf("NO FX_DRIVER_WRITE!!!!\n");
#if 0
            /* Calculate the RAM disk sector offset */
            destination_buffer =  (UCHAR *)FX_SRAM_DISK_BASE_ADDRESS +
                                  ((media_ptr->fx_media_driver_logical_sector +  media_ptr->fx_media_hidden_sectors) * media_ptr->fx_media_bytes_per_sector);
            /* Calculate destination buffer end address */
            destination_buffer_end = destination_buffer + (media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);

            /* Check destination buffer does not exceed sram disk end address */
            if (destination_buffer_end  > sram_disk_end)
            {
              media_ptr -> fx_media_driver_status =  FX_PTR_ERROR;
              break;
            }
            else
            {
              /* Copy the source to the RAM sector.  */
              _fx_utility_memory_copy(media_ptr->fx_media_driver_buffer, destination_buffer,
                                      media_ptr->fx_media_driver_sectors * media_ptr->fx_media_bytes_per_sector);

              /* Successful driver request.  */
              media_ptr -> fx_media_driver_status =  FX_SUCCESS;
              break;
            }
#endif
        }

        case FX_DRIVER_FLUSH:
        {

            /*
             * Nothing to do for the FX_DRIVER_FLUSH Return driver success.
             */
            media_ptr->fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_ABORT:
        {

            /*
             * Nothing to do for the FX_DRIVER_ABORT Return driver success.
             */
            media_ptr->fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_READ:
        {

            /* Calculate the RAM disk boot sector offset, which is at the very beginning of
             * the RAM disk.
             */
            source_buffer =  (UCHAR *)FX_SRAM_DISK_BASE_ADDRESS;
            /* For RAM disk only, pickup the bytes per sector.*/

            bytes_per_sector =  _fx_utility_16_unsigned_read(&source_buffer[FX_BYTES_SECTOR]);

            /* Ensure this is less than the media memory size.  */
            if (bytes_per_sector > media_ptr->fx_media_memory_size)
            {
                media_ptr->fx_media_driver_status =  FX_BUFFER_ERROR;
                break;
            }

            /* Copy the RAM boot sector into the destination.  */
            _fx_utility_memory_copy(source_buffer, media_ptr -> fx_media_driver_buffer,
                                    bytes_per_sector);
            //printf("FX_DR: %08lX %d\n", (uint32_t) source_buffer, bytes_per_sector);
            //print_hex(media_ptr -> fx_media_driver_buffer, bytes_per_sector, 32);
            /* Successful driver request.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
            break;
        }

        case FX_DRIVER_BOOT_WRITE:
        {
        	printf("NO FX_DRIVER_BOOT_WRITE!!!!\n");
#if 0
            /* 
             * Calculate the RAM disk boot sector offset, which is at the very beginning of the RAM disk.
             */ 
            destination_buffer =  (UCHAR *)FX_SRAM_DISK_BASE_ADDRESS;

            /* Copy the RAM boot sector into the destination.  */
            _fx_utility_memory_copy(media_ptr->fx_media_driver_buffer, destination_buffer,
                                    media_ptr->fx_media_bytes_per_sector);

            /* Successful driver request.  */
            media_ptr -> fx_media_driver_status =  FX_SUCCESS;
#endif
            break;
        }

        default:
        {
            /* Invalid driver request.  */
            media_ptr -> fx_media_driver_status =  FX_IO_ERROR;
            break;
        }
    }
}
