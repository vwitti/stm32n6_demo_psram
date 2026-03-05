#### Definitions for THreadx, NetDuo, ... (all RTOS components) ####

if("${PROJECT_OS_TYPE}" STREQUAL "THREADX")

### Check for OS options ###
if("${PROJECT_OS_DEBUG_BSD_SOCKETS}" STREQUAL "1")
	set(project_os_netxduo_enable_bsd_socket_error NX_BSD_PRINT_ERRORS)
endif()

set(project_os_type_defines_specific 
	#### ThreadX Defines (RTOS) ####
	TX_INCLUDE_USER_DEFINE_FILE 
	TX_SINGLE_MODE_SECURE=1
	#### NetXDuo (TCP/IP Stack) ####
	NX_INCLUDE_USER_DEFINE_FILE
	ETH_PHY_1000MBITS_SUPPORTED
	RTL8211_INIT_TO=10000
	MULTI_QUEUE_FEATURE								# New feature to support multiple queues and channels
	#### FileX Defines          ####
	FX_INCLUDE_USER_DEFINE_FILE
	#### Configure File Descriptor used by close() (FileX and BSD socket interface) ####
	FILEX_MAX_FDS=16								# must be less NX_BSD_SOCKFD_START, since 0..2 are STDIN,STDOUT and STDERR, the rest are file handle for FileX 
	NX_BSD_SOCKFD_START=32							# see nxd_bsd.h, close() is redirected to nx_bsd_soc_close for any fd >= NX_BSD_SOCKFD_START
)

endif()

if("${PROJECT_OS_TYPE}" STREQUAL "NOOS")

set(project_os_type_defines_specific 
	ETHERNET_NOT_SUPPORTED							# Without OS (ThreadX)it is not possible to start NetXDuo
)

endif()

set(project_os_type_defines
	${project_os_type_defines_specific}
	PROJECT_OS_FILESYSTEM=${PROJECT_OS_FILESYSTEM}
	PROJECT_OS_TYPE_STRING="${PROJECT_OS_TYPE}"
	OS_TYPE_${PROJECT_OS_TYPE}						# e.g. OS_TYPE_THREADX or OS_TYPE_NOOS
	### Options and Debugging ###
	PROJECT_PREMAIN_SERIAL_CONSOLE=${PROJECT_PREMAIN_SERIAL_CONSOLE}
	PROJECT_OS_USE_BSD_SOCKETS=${PROJECT_OS_USE_BSD_SOCKETS}
	PROJECT_OS_USE_TOUCHGFX_LIB=${PROJECT_OS_USE_TOUCHGFX_LIB}
	PROJECT_OS_USE_4DIAC_LIB=${PROJECT_OS_USE_4DIAC_LIB}
	${project_os_netxduo_enable_bsd_socket_error}	
)
