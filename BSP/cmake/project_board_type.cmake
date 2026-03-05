#### Definitions for Board, Process, STM32 HAL, ,,,,,,, ####

if("${PROJECT_PROG_TYPE}" STREQUAL "FSBL")
set(project_board_type_defines_specific_fsbl
)
endif()

if("${PROJECT_PROG_TYPE}" STREQUAL "APPLI")
set(project_board_type_defines_specific_appli
	STM32N6570_TOUCHGFX_ADD_GPIO=${PROJECT_HW_TOUCHGFX_ADD_GPIO}	# USART used for printf debugging
)
endif()

if("${PROJECT_BOARD_TYPE}" STREQUAL "ASG_EVO")

set(project_asg_evo_board_specific
	PROJECT_HW_ENABLE_I2C1=${PROJECT_HW_ENABLE_I2C1}				# Control I2C1
	PROJECT_HW_ENABLE_CAN=${PROJECT_HW_ENABLE_CAN}					# Control FDCAN 1,2
	PROJECT_HW_ENABLE_SPI=${PROJECT_HW_ENABLE_SPI}					# Control SPI2,4
)
endif()

set(project_board_type_defines_specific
	#### STM32 HAL ####
	USE_HAL_DRIVER 
	STM32N657xx
	#### STM32M6570-DK BSP Setting ####
	USE_DMA2D_TO_FILL_RGB_RECT=1
	USE_BSP_CPU_CACHE_MAINTENANCE=1
	#### BOARD Definitions ####
	SPI_FLASH_MEMORY_SIZE=0x8000000									# Capacity of external Flash Memory MX66UW1G45G
	STM32N6570_SERIAL_CONSOLE=${PROJECT_HW_SERIAL_CONSOLE}			# USART used for printf debugging
	STM32N6570_CPU_CLOCK=${PROJECT_HW_CPU_CLOCK}					# Clock of CPU
	${project_asg_evo_board_specific}
)

set(project_board_type_defines
	${project_board_type_defines_specific}
	${project_board_type_defines_specific_fsbl}
	${project_board_type_defines_specific_appli}
	PROJECT_BOARD_TYPE_STRING="${PROJECT_BOARD_TYPE}"
	BOARD_TYPE_${PROJECT_BOARD_TYPE}					# e.g. BOARD_TYPE_ASG_EVO or BOARD_TYPE_N6570_DK
)