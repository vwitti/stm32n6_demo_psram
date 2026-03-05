/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.c
  * @author  MCD Application Team
  * @brief   NetXDuo applicative file
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
#include <stdbool.h>
#include "tcsglobal/asg_evo.h"
#include "SysLog/Syslog.h"
#include "Utils/ip_utils.h"
#include "Utils/printf_utils.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/app_netxduo.h"
#include "Common/Inc/Init/app_filex.h"

/* Private includes ----------------------------------------------------------*/
#include "nxd_ftp_client.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

static NX_FTP_CLIENT ftp_client;
static NX_PACKET *rv_packet_ptr;
static uint8_t recv_fragment[DEFAULT_PAYLOAD_SIZE];
static FX_FILE  file;
static bool connection_open;

UINT MX_NetXDuo_Init_FTP_CreatOpen(void)
{
	  UINT ret = NX_SUCCESS;
	  NX_PACKET_POOL * packet_pool = get_MX_NetXDuo_PacketPool();
	  NX_IP * ip_inst = get_MX_NetXDuo_Instance();

	  //printf("Start NetXDuo FTP client\n");

	  /* Create the FTP client */
	  ret = nx_ftp_client_create(&ftp_client, "FTP-Client", ip_inst, 1024, packet_pool);
	  if (ret != NX_SUCCESS)
	  {
		printf("nx_ftp_client_create failed: %u\n", ret);
	    return NX_FTP_ERROR;
	  }

	  /* Enable the passive mode */
	  nx_ftp_client_passive_mode_set(&ftp_client, NX_TRUE);

	  /* Open connection to server */
	  ULONG server_ip = ip_utils_convert_ipstr_to_uint32(App_NetXDuo_GetFTP_Server_Address());
	  ret = nx_ftp_client_connect(&ftp_client,
	                                 server_ip,
									 App_NetXDuo_GetFTP_Server_User(),
									 App_NetXDuo_GetFTP_Server_Pass(),
	                                 NETX_DUO_FTP_SERVER_TIMEOUT);			// wait max 5 secs for FTP server

	  if (ret != NX_SUCCESS)
	  {
	      printf("FTP connect failed: %u\n", ret);
	      return NX_FTP_ERROR;
	  }

	  printf("Connection to ftp server %s established\n", App_NetXDuo_GetFTP_Server_Address());
	  connection_open = true;
	  return NX_SUCCESS;
}

UINT MX_NetXDuo_Init_FTP_Close(void)
{
	if(connection_open == true)
	{
		  // Close connection again
		  UINT ret = nx_ftp_client_disconnect(&ftp_client, NETX_DUO_FTP_SERVER_TIMEOUT);
		  if (ret != NX_SUCCESS)
		  {
		      printf("FTP disconnect failed: %u\n", ret);
		      return NX_FTP_ERROR;
		  }

		  printf("Connection to ftp server %s closed\n", App_NetXDuo_GetFTP_Server_Address());
		  return NX_SUCCESS;
	}
	printf("FTP: no connection open.\n");
	return NX_SUCCESS;
}

static UINT MX_NetXDuo_Init_FTP_DownloadFileInt(const char * mount_path, const char * filename)
{
	UINT ret;
	CHAR * fx_filename = (CHAR *) filename;

	/* Open file on SD card to write */
	FX_MEDIA * media = MX_FileX_Get_Media(mount_path);

	/* Delete and create */
	fx_file_delete(media, fx_filename);
	ret = fx_file_create(media, fx_filename);
	if (ret != FX_SUCCESS)
	{
	    printf("FileX: Cant create file %s, error: %u\n", filename, ret);
	    return ret;
	}

	/* Datei zum Schreiben oeffnen */
	ret = fx_file_open(media, &file, fx_filename, FX_OPEN_FOR_WRITE);
	if (ret != FX_SUCCESS)
	{
		printf("FileX: Cant open file %s, error: %u\n", filename, ret);
		return ret;
	}

	/* Dateizeiger auf Anfang setzen (optional, aber sauber) */
	fx_file_seek(&file, 0);

	ret  = nx_ftp_client_file_open(&ftp_client, fx_filename, NX_FTP_OPEN_FOR_READ, NETX_DUO_FTP_SERVER_TIMEOUT);
	if (ret) {
		printf("FTP: cant open %s for download, error: %u\n", filename, ret);
		return ret;
	}

	/* READ from FTP and write to file */
	bool eof = false;
	do
	{
		  ret = nx_ftp_client_file_read(&ftp_client, &rv_packet_ptr, NETX_DUO_FTP_SERVER_TIMEOUT);
		  if(ret == NX_FTP_END_OF_FILE)
		  {
			  //printf("FTP: eof reached : %u\n", ret);
			  eof = true;
		  }
		  else if (ret ) {
		      printf("FTP: cant read file data: %u\n", ret);
		      eof = true;
		  }

		  if(eof == false)
		  {
			  ULONG pck_copy_length;

			  nx_packet_data_retrieve(rv_packet_ptr, recv_fragment, &pck_copy_length);

			  ret = fx_file_write(&file, recv_fragment, pck_copy_length);
			  if (ret ) {
				  printf("FileX: cant write SD-Card: %u\n", ret);
				  eof = true;
			  }
			  //print_hex_ascii(recv_fragment, pck_copy_length, 16);

			  // Free memory
			  nx_packet_release(rv_packet_ptr);
		  }
	} while(eof == false);

	/* Datei schließen (wichtig!) */
	fx_file_close(&file);

	/* FAT aktualisieren */
	fx_media_flush(media);

	// Close file
	ret = nx_ftp_client_file_close(&ftp_client, NETX_DUO_FTP_SERVER_TIMEOUT);
	if (ret ) {
		printf("FTP: cant close file: %u\n", ret);
	}
	printf("FTP: successful download: %s\n", fx_filename);
	return ret;
}

UINT MX_NetXDuo_Init_FTP_DownloadFile(const char * filename)
{
    return MX_NetXDuo_Init_FTP_DownloadFileInt("/" FTP_DOWNLOAD_PATH, filename);
}
