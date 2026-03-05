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
#include "tcsglobal/asg_evo.h"
#include "SysLog/Syslog.h"
#include "Common/Inc/Init/start_screen_lcd.h"
#include "Common/Inc/Init/app_netxduo.h"
#include "Common/Inc/Init/app_filex.h"
#include "Utils/ip_utils.h"
#include "Utils/kv_store.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

static kv_store_t ip_config_list;
static char str_ftp_server[20];
static char str_ftp_user[20];
static char str_ftp_pass[20];
static UINT uint_ftp_port;

UINT App_NetXDuo_SetupIpConfiguration(void)
{
	const char * val;
	printf("NetXDuo: Setup IP Configuration %s\n", PATH_FILE_IP_CONFIG_FILE);

	// Read IP config file
	kv_init(&ip_config_list);
	kv_load_from_file(&ip_config_list, PATH_FILE_IP_CONFIG_FILE);

	printf("NetXDuo: Config file %s\n", PATH_FILE_IP_CONFIG_FILE);
	val = kv_get(&ip_config_list, IP_CONFIG_USE_DHCP);
	if(val != NULL) printf("%s\t\t%s\n", (char *) IP_CONFIG_USE_DHCP, val);

	val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_ADDR);
	if(val != NULL) printf("%s\t\t%s\n", IP_CONFIG_STATIC_IP_ADDR, val);

	val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_MASK);
	if(val != NULL) printf("%s\t\t%s\n", IP_CONFIG_STATIC_IP_MASK, val);

	val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_GATEWAY);
	if(val != NULL) printf("%s\t%s\n", IP_CONFIG_STATIC_IP_GATEWAY, val);

	val = kv_get(&ip_config_list, IP_CONFIG_FTP_SERVER_PORT);
	if(val != NULL)
	{
		char *endptr;
		uint_ftp_port = strtol(val, &endptr, 10);
		printf("%s\t\t%d\n", IP_CONFIG_FTP_SERVER_PORT, uint_ftp_port);
	}

	str_ftp_server[0]=0;
	val = kv_get(&ip_config_list, IP_CONFIG_FTP_SERVER_IP);
	if(val != NULL)
	{
		strncpy(str_ftp_server, val, sizeof(str_ftp_server));
		printf("%s\t\t%s\n", IP_CONFIG_FTP_SERVER_IP, str_ftp_server);
	}

	str_ftp_user[0]=0;
	val = kv_get(&ip_config_list, IP_CONFIG_FTP_USER);
	if(val != NULL)
	{
		strncpy(str_ftp_user, val, sizeof(str_ftp_user));
		printf("%s\t\t%s\n", IP_CONFIG_FTP_USER, str_ftp_user);
	}

	str_ftp_pass[0]=0;
	val = kv_get(&ip_config_list, IP_CONFIG_FTP_PASS);
	if(val != NULL)
	{
		strncpy(str_ftp_pass, val, sizeof(str_ftp_pass));
		printf("%s\t\t%s\n", IP_CONFIG_FTP_PASS, str_ftp_pass);
	}

	return 0;
}

UINT App_NetXDuo_Configure_IP_Address(void)
{
	UINT ret;
	const char * val;
	val = kv_get(&ip_config_list, IP_CONFIG_USE_DHCP);

	if(val == NULL)
	{
		return -1; // NULL
	}

	if(strcmp(val, "0"))
	{
		/* Configure DHCP Client and request IP address */
	    printf("NetXDuo: MX_NetXDuo_Init_DHCP\n");
	    ret = MX_NetXDuo_Init_DHCP(NX_GetBytePoolDesc());
	    if(ret != TX_SUCCESS)
	    {
	    	printf("NetXDuo: Stack Init fail");
	    	return -1;
	    }

		/* Wait a limited time for an IP Address from DHCP Client */
		ret = MX_NetXDuo_Init_DHCP_WaitForIp(DHCP_FSBL_TIMEOUT);
		if(ret == TX_NO_EVENTS)
		{
		  StartScreenLcd_WriteLine("DHCP timed out, no IP address received for %d ms", DHCP_FSBL_TIMEOUT);
		  return -1;
		}
	}
	else
	{
		val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_ADDR);
		if(val == NULL)
		{
			return -1; // NULL
		}
		uint32_t ipaddr = ip_utils_convert_ipstr_to_uint32(val);

		val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_MASK);
		if(val == NULL)
		{
			return -1; // NULL
		}
		uint32_t ipmask = ip_utils_convert_ipstr_to_uint32(val);

		val = kv_get(&ip_config_list, IP_CONFIG_STATIC_IP_GATEWAY);
		if(val == NULL)
		{
			return -1; // NULL
		}
		uint32_t gateway = ip_utils_convert_ipstr_to_uint32(val);

		/* Set IP address for instance */
		ret = nx_ip_address_set(get_MX_NetXDuo_Instance(), ipaddr, ipmask);
		if (ret != NX_SUCCESS)
		{
			return NX_NOT_SUCCESSFUL;
		}

		ret = nx_ip_gateway_address_set(get_MX_NetXDuo_Instance(), gateway);
		if (ret != NX_SUCCESS)
		{
			return NX_NOT_SUCCESSFUL;
		}
		MX_NetXDuo_DumpAddress();
	}
	return 0;
}

char * App_NetXDuo_GetFTP_Server_Address()
{
	return str_ftp_server;
}

char * App_NetXDuo_GetFTP_Server_User()
{
	return str_ftp_user;
}

char * App_NetXDuo_GetFTP_Server_Pass()
{
	return str_ftp_pass;
}

UINT App_NetXDuo_GetFTP_Server_Port()
{
	return uint_ftp_port;
}
