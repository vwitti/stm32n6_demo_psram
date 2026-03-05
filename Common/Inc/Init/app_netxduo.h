/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_netxduo.h
  * @author  MCD Application Team
  * @brief   NetXDuo applicative header file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_INIT_NETXDUO_H__
#define __COMMON_INIT_NETXDUO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "BSP/Config/Middleware/middleware_config.h"
#include "nx_shaper.h"
#include "nx_api.h"
#include "nx_stm32_eth_driver.h"

/* Private includes ----------------------------------------------------------*/
typedef enum {
	teNetXDuoPacketPoolId_Global=0,		// MUST BE FIRST AND 0
	teNetXDuoPacketPoolId_Last
} teNetXDuoPacketPoolId;

/* Exported types ------------------------------------------------------------*/
typedef struct
{
    char *   name;				/* Name of pool */
    uint32_t  size;
    uint32_t  total_packets;
	uint32_t  free_packets;
	uint32_t  empty_pool_requests;
	uint32_t  empty_pool_suspensions;
	uint32_t  invalid_packet_releases;
}  tsNetXDuoPacketPoolInfo;

/* Exported constants --------------------------------------------------------*/
#define IP_CONFIG_USE_DHCP			"USE_DHCP"
#define IP_CONFIG_STATIC_IP_ADDR	"STATIC_IP_ADDR"
#define IP_CONFIG_STATIC_IP_MASK	"STATIC_IP_MASK"
#define IP_CONFIG_STATIC_IP_GATEWAY	"STATIC_IP_GATEWAY"
#define IP_CONFIG_FTP_SERVER_PORT	"FTP_SERVER_PORT"
#define IP_CONFIG_FTP_SERVER_IP		"FTP_SERVER_IP"
#define IP_CONFIG_FTP_USER			"FTP_USER"
#define IP_CONFIG_FTP_PASS			"FTP_PASS"

/* Exported macro ------------------------------------------------------------*/
#define NULL_ADDRESS              IP_ADDRESS(0,0,0,0)

/* All Syslog message are send to this address */
#define SYSLOG_DEFAULT_ADDRESS    IP_ADDRESS(192, 168, 178, 54)

#define PRINT_IP_ADDRESS(addr) do { \
                                                printf("STM32 %s: %lu.%lu.%lu.%lu\n", #addr, \
                                    (addr >> 24) & 0xff, \
                                    (addr >> 16) & 0xff, \
                                    (addr >> 8) & 0xff, \
                                     addr& 0xff);\
                                  }while(0)

/* USER CODE END EM */
/* Key in ip config file */



/* Exported functions prototypes ---------------------------------------------*/
TX_BYTE_POOL * NX_GetBytePoolDesc(void);
NX_IP * get_MX_NetXDuo_Instance(void);
NX_PACKET_POOL * get_MX_NetXDuo_PacketPool(void);
UINT MX_NetXDuo_Init(VOID *memory_ptr);
UINT App_NetXDuo_GetPacketPoolInfo(teNetXDuoPacketPoolId id, tsNetXDuoPacketPoolInfo * info);
void MX_NetXDuo_DumpAddress(void);
UINT App_NetXDuo_SetupIpConfiguration(void);
UINT App_NetXDuo_Configure_IP_Address(void);
char * App_NetXDuo_GetFTP_Server_Address();
char * App_NetXDuo_GetFTP_Server_User();
char * App_NetXDuo_GetFTP_Server_Pass();
UINT App_NetXDuo_GetFTP_Server_Port();

/* FTP API */
#define NETX_DUO_FTP_SERVER_TIMEOUT		(5000)
UINT MX_NetXDuo_Init_FTP_CreatOpen(void);
UINT MX_NetXDuo_Init_FTP_Close(void);
UINT MX_NetXDuo_Init_FTP_DownloadFile(const char * filename);

/* DHCP API */
UINT   MX_NetXDuo_Init_DHCP(VOID *memory_ptr);
UINT   MX_NetXDuo_Init_DHCP_WaitForIp(ULONG time);
ULONG  MX_NetXDuo_Init_DHCP_get_own_ip();
ULONG  MX_NetXDuo_Init_DHCP_get_server_ip();

/* NetX Instance Thread */
#define NX_IP_INSTANCE_PRIORITY          	PRIO_COMM_EVENT
#define NX_IP_INSTANCE_THREAD_SIZE       	2048
#define NX_IP_INSTANCE_DEFAULT_IP_ADDRESS   0
#define NX_IP_INSTANCE_DEFAULT_IP_MASK      0

/* NetX Link Check Thread */
#define LINKUP_THREAD_STACK_SIZE		 	2048
#define LINKUP_THREAD_PRIORITY           	PRIO_BACKGROUND
#define LINKUP_THREAD_TIMESLICE          	TIME_SLICE_BACKGROUND
#define LINKUP_THREAD_CHECK_CONN         	500		/* [ms] */

/* NetX DHCP Thread */
#define NX_APP_THREAD_DHCP_START_STACKSIZE  2048
#define NX_APP_THREAD_DHCP_START_PRIORITY   PRIO_COMM_TIMESLICE //PRIO_BACKGROUND
#define NX_APP_THREAD_DHCP_START_TIMESLICE  TIME_SLICE_BACKGROUND
// DHCP Definitions
#define DHCP_EV_IP_ADDR_RECEIVED			(0x0001)
#define DHCP_FSBL_TIMEOUT					(5000)		/* [ms] Wait time for getting an ip address */

/* Private defines -----------------------------------------------------------*/

 /*Packet payload size */
#define DEFAULT_PAYLOAD_SIZE                1536
#define PACKET_PAYLOAD_SIZE              	1536
 /* APP Cache size  */
#define DEFAULT_ARP_CACHE_SIZE    			1024
#define ARP_CACHE_SIZE                   	1024

#define NX_APP_PACKET_POOL_SIZE          	((DEFAULT_PAYLOAD_SIZE + sizeof(NX_PACKET)) * NX_APP_PACKET_NUM_PACKETS)

#ifdef __cplusplus
}
#endif
#endif /* __COMMON_INIT_NETXDUO_H__ */
