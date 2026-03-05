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
#include "Utils/ip_utils.h"

/* Private includes ----------------------------------------------------------*/
#include "nxd_dhcp_client.h"
#if PROJECT_OS_USE_BSD_SOCKETS == 1
#include "nxd_bsd.h"
#endif
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
NX_PACKET_POOL NxAppPool;				/* Paket Pool für Daten zum empfangen versenden */
NX_IP          NetXDuoEthIpInstance;

/* Private function prototypes -----------------------------------------------*/

NX_IP * get_MX_NetXDuo_Instance(void)
{
	return &NetXDuoEthIpInstance;
}

NX_PACKET_POOL * get_MX_NetXDuo_PacketPool(void)
{
	return &NxAppPool;
}

void MX_NetXDuo_DumpAddress(void)
{
	uint32_t ipaddr;
	uint32_t ipmask;
	uint32_t gateway;
	char ipaddr_str[20];
	char ipmask_str[20];

	nx_ip_address_get(get_MX_NetXDuo_Instance(), &ipaddr, &ipmask);
	ip_utils_convert_uint32_to_ipstr(ipaddr, ipaddr_str, sizeof(ipaddr_str));
	ip_utils_convert_uint32_to_ipstr(ipmask, ipmask_str, sizeof(ipmask_str));
	StartScreenLcd_WriteLine("NetXDuo: Address=%s (Mask=%s)", ipaddr_str, ipmask_str);

	nx_ip_gateway_address_get(&NetXDuoEthIpInstance, &gateway);
	ip_utils_convert_uint32_to_ipstr(gateway, ipaddr_str, sizeof(ipaddr_str));
	StartScreenLcd_WriteLine("NetXDuo: Gateway=%s", ipaddr_str);
}

/**
  * @brief  Application NetXDuo Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_NetXDuo_Init(VOID *memory_ptr)
{
  UINT ret = NX_SUCCESS;

  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
  CHAR *pointer;

  printf("Start NetXDuo Stack\n");

  /* Initialize the NetXDuo system. */
  nx_system_initialize();

  /* Allocate the memory for packet_pool.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, NX_APP_PACKET_POOL_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the Packet pool to be used for packet allocation,
   * If extra NX_PACKET are to be used the NX_APP_PACKET_POOL_SIZE should be increased
   */
  ret = nx_packet_pool_create(&NxAppPool, "NetXDuo App Pool", DEFAULT_PAYLOAD_SIZE, pointer, NX_APP_PACKET_POOL_SIZE);

  if (ret != NX_SUCCESS)
  {
    return NX_POOL_ERROR;
  }

  /* Allocate the memory for Ip_Instance */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, NX_IP_INSTANCE_THREAD_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Create the main NX_IP instance */
  ret = nx_ip_create(&NetXDuoEthIpInstance, "NetX Ip instance", NX_IP_INSTANCE_DEFAULT_IP_ADDRESS, NX_IP_INSTANCE_DEFAULT_IP_MASK, &NxAppPool, nx_stm32_eth_driver,
                     pointer, NX_IP_INSTANCE_THREAD_SIZE, NX_IP_INSTANCE_PRIORITY);
  if (ret != NX_SUCCESS)
  {
    return NX_NOT_SUCCESSFUL;
  }

  /* Allocate the memory for ARP */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, DEFAULT_ARP_CACHE_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* Enable the ARP protocol and provide the ARP cache size for the IP instance */
  /* USER CODE BEGIN ARP_Protocol_Initialization */
  /* USER CODE END ARP_Protocol_Initialization */
  ret = nx_arp_enable(&NetXDuoEthIpInstance, (VOID *)pointer, DEFAULT_ARP_CACHE_SIZE);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_SUCCESSFUL;
  }

  /* Enable the ICMP */
  /* USER CODE BEGIN ICMP_Protocol_Initialization */
  /* USER CODE END ICMP_Protocol_Initialization */
  ret = nx_icmp_enable(&NetXDuoEthIpInstance);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_SUCCESSFUL;
  }

  /* Enable TCP Protocol */
  /* USER CODE BEGIN TCP_Protocol_Initialization */
  /* USER CODE END TCP_Protocol_Initialization */
  ret = nx_tcp_enable(&NetXDuoEthIpInstance);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_SUCCESSFUL;
  }

  /* Enable the UDP protocol required for  DHCP communication */
  /* USER CODE BEGIN UDP_Protocol_Initialization */
  /* USER CODE END UDP_Protocol_Initialization */
  ret = nx_udp_enable(&NetXDuoEthIpInstance);

  if (ret != NX_SUCCESS)
  {
    return NX_NOT_SUCCESSFUL;
  }

#if PROJECT_OS_USE_BSD_SOCKETS == 1
  printf("Start NetXDuo BSD Socket API\n");
  /* Now initialize BSD Socket Wrapper */
  /* Allocate the memory for Ip_Instance */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, NX_IP_INSTANCE_THREAD_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  ret = (UINT)bsd_initialize (&NetXDuoEthIpInstance, &NxAppPool, pointer, NX_IP_INSTANCE_THREAD_SIZE, NX_IP_INSTANCE_PRIORITY);
  if(ret != 0)
  {
	  return NX_NOT_SUCCESSFUL;
  }
#endif
  return ret;
}

UINT App_NetXDuo_GetPacketPoolInfo(teNetXDuoPacketPoolId id, tsNetXDuoPacketPoolInfo * info)
{
	UINT ret = TX_NO_INSTANCE;
	NX_PACKET_POOL *pool;
	ULONG total_packets;
	ULONG free_packets;
	ULONG empty_pool_requests;
	ULONG empty_pool_suspensions;
	ULONG invalid_packet_releases;

	if(info == NULL)
	{
		return TX_NO_INSTANCE;
	}
	switch(id)
	{
	case teNetXDuoPacketPoolId_Global:
		pool = &NxAppPool;
		info->name = NxAppPool.nx_packet_pool_name;
		info->size = NX_APP_PACKET_POOL_SIZE;
		break;
	default:
		return TX_NO_INSTANCE;
	}

	ret = nx_packet_pool_info_get(pool, &total_packets, &free_packets, &empty_pool_requests, &empty_pool_suspensions, &invalid_packet_releases);
	if(ret == TX_SUCCESS)
	{
		info->name = NxAppPool.nx_packet_pool_name;
		info->total_packets = total_packets;
		info->free_packets = free_packets;
		info->empty_pool_requests = empty_pool_requests;
		info->empty_pool_suspensions = empty_pool_suspensions;
		info->invalid_packet_releases = invalid_packet_releases;
		//Log_Printf(LOG_LEVEL_DEBUG, "Pool:%15s, Size:%6lX, Total:%6ld Free:%6ld, Empty:%6ld Susp:%6ld InvRel:%6ld", info->name,
		//		info->size, info->total_packets, info->free_packets,
		//		info->empty_pool_requests, info->empty_pool_suspensions, info->invalid_packet_releases);
		printf("Pool:%15s, Size:%6lX, Total:%6ld Free:%6ld, Empty:%6ld Susp:%6ld InvRel:%6ld\n", info->name,
				info->size, info->total_packets, info->free_packets,
				info->empty_pool_requests, info->empty_pool_suspensions, info->invalid_packet_releases);
	}
	return ret;
}
