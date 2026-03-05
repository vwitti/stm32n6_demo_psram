message(STATUS "----------------------------- Cmake Build Project -----------------------------------")
message(STATUS "███╗   ██╗ ██████╗ ███████╗███████╗ ██████╗         ███████╗██╗   ██╗ █████╗ ██╗     ")
message(STATUS "████╗  ██║██╔════╝ ██╔════╝╚════██║██╔═████╗        ██╔════╝██║   ██║██╔══██╗██║     ")
message(STATUS "██╔██╗ ██║███████╗ ███████╗    ██╔╝██║██╔██║        █████╗  ██║   ██║███████║██║     ")
message(STATUS "██║╚██╗██║██╔═══██╗╚════██║   ██╔╝ ████╔╝██║        ██╔══╝  ╚██╗ ██╔╝██╔══██║██║     ")
message(STATUS "██║ ╚████║╚██████╔╝███████║   ██║  ╚██████╔╝███████╗███████╗ ╚████╔╝ ██║  ██║███████╗")
message(STATUS "╚═╝  ╚═══╝ ╚═════╝ ╚══════╝   ╚═╝   ╚═════╝ ╚══════╝╚══════╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝")                                                                                                   
message(STATUS "                                                                                     ")
message(STATUS "                            ███████╗███████╗██████╗ ██╗                              ")
message(STATUS "                            ██╔════╝██╔════╝██╔══██╗██║                              ")
message(STATUS "                            █████╗  ███████╗██████╔╝██║                              ")
message(STATUS "                            ██╔══╝  ╚════██║██╔══██╗██║                              ")
message(STATUS "                            ██║     ███████║██████╔╝███████╗                         ")
message(STATUS "                            ╚═╝     ╚══════╝╚═════╝ ╚══════╝                         ")
message(STATUS "-------------------------------------------------------------------------------------")

#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements.
#        For debug build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug VERBOSE=1 -j
#        For release build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make -C Release VERBOSE=1 -j
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

################## PROJECT SETUP ######################################
set (PROJECT_BASENAME         		"N6570_EVAL")   # Arbitrary project name
set (PROJECT_OS_TYPE          		"THREADX")		# THREADX, NOOS      --> includes "project_os_type.cmake"
set (PROJECT_BOARD_TYPE       		"N6570_DK")		# N6570_DK, ASG_EVO  --> includes "project_board_type.cmake" and selects BSP folder
set (PROJECT_PROG_TYPE        		"FSBL")			# FSBL, APPLI        --> includes "project_prog_type.cmake"

### Options ###
set (PROJECT_STM32CUBE_BUG_WORKAROUNDS		"1")            # This are workarounds for known bugs of STM32CubeN6 until solved by ST (or not)
set (PROJECT_HW_CPU_CLOCK					"800")		   	# CPU Clock in MHz (600 oder 800)
set (PROJECT_HW_SERIAL_CONSOLE      		"2")            # 1 = USART1 (used by ST-Link, e.g. /dev/ttyACM0)
                                                    # 2 = USART2 (on Arduino Extension Board, e.g. /dev/ttyUSB0 NOTE: TX Pin later used by touchgfx lib)
set (PROJECT_OS_FILESYSTEM					"1")	        # Use FileX filesystem
set (PROJECT_OS_USE_BSD_SOCKETS 			"0")			# Use BSD Socket Interface with NetXDuo
set (PROJECT_OS_USE_TOUCHGFX_LIB 			"0")			# Use touchGFX library

### Debugging ###
set (PROJECT_PREMAIN_SERIAL_CONSOLE 		"0")			# Enable premain serial console write for debugging (just for debugging)
set (PROJECT_OS_DEBUG_BSD_SOCKETS 			"0")			# Enable printf Debugging for BSD socket interface (defines NX_BSD_PRINT_ERRORS)

###################################### BASIC SETTING ######################################
# Updater check for PROJECT_PROG_TYPE part to determine type of binary
set (PROJECT_BUILD_NAME       "${PROJECT_BASENAME}.${PROJECT_PROG_TYPE}")     
project(${PROJECT_BUILD_NAME})
enable_language(ASM)

include (scripts/cmake/projects.cmake)
set (LINKER_SCRIPT            "BSP/${PROJECT_BOARD_TYPE}/BSP/${PROJECT_PROG_TYPE}/STM32N657XX_AXISRAM2_fsbl.ld")

set (PROJECT_SOURCES
	# LIST SOURCE FILES HERE
	Startup/startup_stm32n657xx_fsbl.s
    Src/main.c
    Src/stm32n6xx_hal_msp.c
	Src/system_stm32n6xx_fsbl.c
	Src/systemthread_init.c
    #Src/systemthread_test.c
    ### Board Support package with Hardware Initialisation ###
    BSP/${PROJECT_BOARD_TYPE}/BSP/eth.c
    #BSP/${PROJECT_BOARD_TYPE}/BSP/fx_stm32_sd_driver_glue.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/gpio_peripherals.c
    #BSP/${PROJECT_BOARD_TYPE}/BSP/sd.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/stm32_dev_handles.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/usart.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/${PROJECT_PROG_TYPE}/bsec.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/${PROJECT_PROG_TYPE}/hpdma.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/${PROJECT_PROG_TYPE}/mcu.c
    BSP/${PROJECT_BOARD_TYPE}/BSP/${PROJECT_PROG_TYPE}/xspi.c
    ### Init Code ###
    BSP/${PROJECT_BOARD_TYPE}/tx_initialize_low_level.S
    ### Common Code ###
    Common/Src/Init/app_azure_rtos.c
    Common/Src/Init/app_filex.c
    Common/Src/Init/app_filex_sd.c
    Common/Src/Init/app_netxduo.c
    #Common/Src/Init/app_netxduo_dhcp.c
    #Common/Src/Init/app_netxduo_ftp.c
    #Common/Src/Init/app_netxduo_ipconfig.c
    Common/Src/Init/app_threadx.c
    Common/Src/Init/error_handler.c
    Common/Src/Init/start_screen_lcd.c
    Common/Src/Init/syscalls_HAL_uart.c
    Common/Src/Init/syscalls.c
    Common/Src/Init/syscalls_close_socket.c
    Common/Src/Init/syscalls_fstat.c
	Common/Src/Init/sysmem.c
	Common/Src/Init/systemtick_init.c
	Common/Src/Init/extmem/extmem_info.c
    Common/Src/Init/extmem/extmem_manager.c
    Common/Src/Init/hw/system_clocks.c
    Common/Src/Init/hw/stm32n6xx_it.c
    Common/Src/Init/hw/stm32n6xx_it_c_handler.c
    Common/Src/Init/hw/coredump.c
    #Common/Src/Init/extmem/fsinit_sdcard.c
    #Common/Src/Init/extmem/fsinit_tcsromfs.c
    Common/Src/Init/extmem/fsinit_psramfs.c
    Common/Src/Test/psram_test.c
    Common/Src/Test/perf_test.c
	Common/Src/Update/firmware_update.c
	#libraries/Middlewares/ST/filex/common/drivers/fx_stm32_sd_driver.c
	libraries/Middlewares/ST/filex/common/drivers/fx_stm32_xspi_direct.c
	libraries/Middlewares/ST/filex/common/drivers/fx_stm32_psram_memmapped.c
)

set (PROJECT_DEFINES
	# LIST COMPILER DEFINITIONS HERE
	BUILD_VERSION_MAJOR="1"
	BUILD_VERSION_MINOR="0"
	BUILD_VERSION_PATCH="1"
    )

######################################## INCLUDES #########################################

##### Global include path (all project parts and libraries) #####
set (PROJECT_INCLUDES
	${ASG_EVO_PROJECT_PATH}
	BSP/${PROJECT_BOARD_TYPE}						# Base directory for Board Support package
	BSP/${PROJECT_BOARD_TYPE}/BSP/Config/Stm32Hal	# Conf File for STM32 HAL
	BSP/${PROJECT_BOARD_TYPE}/BSP/Config/Middleware	# Conf File for STM32 Middleware (ThreadX, NetxDuo, ....)
)

####################################### EXECUTABLE ########################################
if (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_EXECUTABLE})
	add_executable(${PROJECT_BUILD_NAME} ${PROJECT_SOURCES})
	include (${ASG_EVO_SCRIPT_PATH}/cmake/prebuild.cmake)
	include (${ASG_EVO_SCRIPT_PATH}/cmake/postbuild.cmake)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
	add_library(${PROJECT_BUILD_NAME} ${PROJECT_SOURCES})
endif()

################################## COMPILER DEFINITIONS ###################################
include (BSP/cmake/project_os_type.cmake)
include (BSP/cmake/project_board_type.cmake)
include (BSP/cmake/project_prog_type.cmake)
set(ASG_EVO_Defines_Syms 
	${project_os_type_defines}
	${project_board_type_defines}
	${project_prog_type_defines}
    $<$<CONFIG:Debug>:DEBUG>
)
include (${ASG_EVO_SCRIPT_PATH}/cmake/stm32n6_compiler.cmake)

############################### PROJECT SPECIFIC INCLUDES ###############################
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${ASG_EVO_TCS_PATH}
	Common/Inc/Init/extmem								# The ST libraries include direct
	${ASG_EVO_LIBRARY_PATH}/Common						# All system components
	${ASG_EVO_LIBRARY_PATH}								# path to Utilities
	${ASG_EVO_TCS_PATH}/FSBL_Assets/generated           # Images for FSBL bootcode and other artefacts
	# STM32 HAL Layer
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Device/ST/STM32N6xx/Include
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Include
	# BSP Layer
	${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK
	${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK/Components/Common
	# Middleware
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/filex/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/filex/ports/generic/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/common/drivers/ethernet
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/addons/dhcp
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/addons/ftp
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/tsn/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/ports/cortex_m55/gnu/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager/custom
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager/custom/memories
)

#################################### BUILD DIRECTORIES ####################################
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Drivers)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Common/AsgAssert)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Common/SysLayer)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Common/SysLog)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Common/Utils)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/filex)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager)
add_subdirectory(${ASG_EVO_LIBRARY_PATH}/Utilities/STM32N6/lcd)

##################################### LINK LIBRARIES ######################################
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined libraries
    # ------- common -------
    lb_n6570_dk
    lb_syslayer
    lb_syslog
    lb_asgassert
    lb_utils
    # ------- driver -------
    lb_stm32n6drv
    # ------- middleware -------
    lb_stm32_extmem_mm
    lb_threadx
    lb_netxduo
    lb_filex
    # ------- utilities ----
    lb_utils_stm32n6
)

