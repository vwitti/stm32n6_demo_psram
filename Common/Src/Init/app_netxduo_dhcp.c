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

/* Private includes ----------------------------------------------------------*/
#include "nxd_dhcp_client.h"
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
#define DHCP_EV_IP_ADDR_RECEIVED	(0x0001)

static TX_THREAD      NxAppThread;
static TX_EVENT_FLAGS_GROUP DHCPEvent;
static NX_DHCP        DHCPClient;

/* USER CODE BEGIN PV */
static ULONG          IpAddress;
static ULONG          NetMask;
static ULONG          ServerAddress;

TX_THREAD AppLinkThread;

/* Private function prototypes -----------------------------------------------*/
static VOID ThreadASG_NetX_DHCP_Startup (ULONG thread_input);
static VOID ip_address_change_notify_callback(NX_IP *ip_instance, VOID *ptr);
static VOID ThreadASG_NetX_LinkUp(ULONG thread_input);

ULONG  MX_NetXDuo_Init_DHCP_get_own_ip()
{
	return IpAddress;
}

ULONG  MX_NetXDuo_Init_DHCP_get_server_ip()
{
	return ServerAddress;
}

TX_EVENT_FLAGS_GROUP * MX_NetXDuo_DHCP_Event(void)
{
	return &DHCPEvent;
}

// time in [ms] */
UINT MX_NetXDuo_Init_DHCP_WaitForIp(ULONG time)
{
	ULONG flags;
	UINT ret = tx_event_flags_get(&DHCPEvent,  DHCP_EV_IP_ADDR_RECEIVED, TX_AND, &flags, TX_MS_TO_TICK(time));

	if(ret != TX_SUCCESS)
	{
		printf("Can't wait for DHCP Event\n");
	}
	return ret;
}

/**
  * @brief  Application NetXDuo Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT MX_NetXDuo_Init_DHCP(VOID *memory_ptr)
{
  UINT ret = NX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;
  CHAR *pointer;

  printf("Start NetXDuo DHCP client\n");

  NX_IP * ip_inst = get_MX_NetXDuo_Instance();

  /* Create the DHCP client */
  ret = nx_dhcp_create(&DHCPClient, ip_inst, "DHCP Client");

  if (ret != NX_SUCCESS)
  {
    return NX_DHCP_ERROR;
  }

  /* Allocate the memory for DHCP thread   */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, NX_APP_THREAD_DHCP_START_STACKSIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* set DHCP notification callback  */
  tx_event_flags_create(&DHCPEvent, "DHCP Event");

  /* Create the main thread */
  ret = tx_thread_create(&NxAppThread, "Netx DHCP Startup", ThreadASG_NetX_DHCP_Startup , 0, pointer, NX_APP_THREAD_DHCP_START_STACKSIZE,
		  NX_APP_THREAD_DHCP_START_PRIORITY, NX_APP_THREAD_DHCP_START_PRIORITY, NX_APP_THREAD_DHCP_START_TIMESLICE, TX_AUTO_START);

  if (ret != TX_SUCCESS)
  {
    return TX_THREAD_ERROR;
  }

  /* Allocate the memory for Link thread   */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer, LINKUP_THREAD_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    return TX_POOL_ERROR;
  }

  /* create the Link thread */
  ret = tx_thread_create(&AppLinkThread, "Netx LinkUp Thread", ThreadASG_NetX_LinkUp, 0, pointer, LINKUP_THREAD_STACK_SIZE,
		  LINKUP_THREAD_PRIORITY, LINKUP_THREAD_PRIORITY, LINKUP_THREAD_TIMESLICE, TX_AUTO_START);

  if (ret != TX_SUCCESS)
  {
    return NX_NOT_ENABLED;
  }
  return ret;
}

/**
* @brief  ip address change callback.
* @param ip_instance: NX_IP instance
* @param ptr: user data
* @retval none
*/
static VOID ip_address_change_notify_callback(NX_IP *ip_instance, VOID *ptr)
{
	NX_IP * ip_inst = get_MX_NetXDuo_Instance();

  /* USER CODE BEGIN ip_address_change_notify_callback */
  /* release the semaphore as soon as an IP address is available */
  if (nx_ip_address_get(ip_inst, &IpAddress, &NetMask) != NX_SUCCESS)
  {
	  printf("DHCP: IP addr changed failed!\n");
  }
  if(IpAddress != NULL_ADDRESS)
  {
    tx_event_flags_set(&DHCPEvent, DHCP_EV_IP_ADDR_RECEIVED, TX_OR);
  }
  /* USER CODE END ip_address_change_notify_callback */

}

/**
* @brief  Main thread entry.
* @param thread_input: ULONG user argument used by the thread entry
* @retval none
*/
static VOID ThreadASG_NetX_DHCP_Startup (ULONG thread_input)
{
  UINT ret = NX_SUCCESS;
  ULONG flags;

  NX_IP * ip_inst = get_MX_NetXDuo_Instance();

  /* register the IP address change callback */
  ret = nx_ip_address_change_notify(ip_inst, ip_address_change_notify_callback, NULL);
  if (ret != NX_SUCCESS)
  {
	printf("DHCP: cant register callback for ip addr changeIP addr changed failed!\n");
	goto ThreadASG_NetX_DHCP_Startup_exit;
  }

  /* start the DHCP client */
  ret = nx_dhcp_start(&DHCPClient);
  if (ret != NX_SUCCESS)
  {
	printf("DHCP: cant start DHCP Client.\n");
	goto ThreadASG_NetX_DHCP_Startup_exit;
  }

  StartScreenLcd_WriteLine("Looking for DHCP server..");

  /* wait until an IP address is ready, but do not delete flag */
  if(tx_event_flags_get( &DHCPEvent,  DHCP_EV_IP_ADDR_RECEIVED, TX_AND, &flags, TX_WAIT_FOREVER) != TX_SUCCESS)
  {
	printf("DHCP: cant get event.\n");
	goto ThreadASG_NetX_DHCP_Startup_exit;
  }

  MX_NetXDuo_DumpAddress();
  if(nx_dhcp_server_address_get(&DHCPClient, &ServerAddress) != TX_SUCCESS)
  {
	  printf("DHCP: cant get server address.\n");
  }

  /* the network is correctly initialized, start the WEB server thread */
ThreadASG_NetX_DHCP_Startup_exit:
  /* this thread is not needed any more, we relinquish it */
  tx_thread_relinquish();
  /* USER CODE END Nx_App_Thread_Entry 2 */

}
/* USER CODE BEGIN 1 */

/**
* @brief  Link thread entry
* @param thread_input: ULONG thread parameter
* @retval none
*/
static VOID ThreadASG_NetX_LinkUp(ULONG thread_input)
{
	ULONG flags;
  ULONG actual_status;
  UINT linkdown = 0, status;

  NX_IP * ip_inst = get_MX_NetXDuo_Instance();

  while(1)
  {
    /* Send request to check if the Ethernet cable is connected. */
    status = nx_ip_interface_status_check(ip_inst, 0, NX_IP_LINK_ENABLED,
                                      &actual_status, 10);

    if(status == NX_SUCCESS)
    {
      if(linkdown == 1)
      {
        linkdown = 0;

        /* The network cable is connected. */
        printf("The network cable is connected.\n");

        /* Send request to enable PHY Link. */
        nx_ip_driver_direct_command(ip_inst, NX_LINK_ENABLE,
                                      &actual_status);

        /* Send request to check if an address is resolved. */
        status = nx_ip_interface_status_check(ip_inst, 0, NX_IP_ADDRESS_RESOLVED,
                                      &actual_status, 10);
        if(status == NX_SUCCESS)
        {
          /* Stop DHCP */
          nx_dhcp_stop(&DHCPClient);

          /* Reinitialize DHCP */
          nx_dhcp_reinitialize(&DHCPClient);

          /* Start DHCP */
          nx_dhcp_start(&DHCPClient);

          /* wait until an IP address is ready */
          if(tx_event_flags_get( &DHCPEvent,  DHCP_EV_IP_ADDR_RECEIVED, TX_AND, &flags, TX_WAIT_FOREVER) != TX_SUCCESS)
          {
        		printf("LinkUp: cant get sema.\n");
        		goto ThreadASG_NetX_LinkUp_Sleep;
          }
          PRINT_IP_ADDRESS(IpAddress);
        }
        else
        {
          /* Set the DHCP Client's remaining lease time to 0 seconds to trigger an immediate renewal request for a DHCP address. */
          nx_dhcp_client_update_time_remaining(&DHCPClient, 0);
        }
      }
    }
    else
    {
      if(0 == linkdown)
      {
        linkdown = 1;
        /* The network cable is not connected. */
        printf("The network cable is not connected.\n");
        tx_event_flags_set(&DHCPEvent, DHCP_EV_IP_ADDR_RECEIVED, TX_AND);
        nx_ip_driver_direct_command(ip_inst, NX_LINK_DISABLE, &actual_status);
      }
    }
ThreadASG_NetX_LinkUp_Sleep:
    tx_thread_sleep(TX_MS_TO_TICK(LINKUP_THREAD_CHECK_CONN));
  }
}
