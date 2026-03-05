message(STATUS "------------------------- STM32N6570-DK --------------------------------")

##### Name of Library #####
set(library_name lb_n6570_dk)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes 
	# STM32 HAL Layer
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Device/ST/STM32N6xx/Include
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Include
    # BSP Layer
    STM32N6570-DK
    Components/Common
)

#if("${PROJECT_PROG_TYPE}" STREQUAL "FSBL")
# Use simple graphics lib when toughGFX is not used
if("${PROJECT_OS_USE_TOUCHGFX_LIB}" STREQUAL "0")
set(add_discovery_lcdt_driver 
	STM32N6570-DK/stm32n6570_discovery_lcd.c
)
endif()


set (LIB_SOURCES
	${add_discovery_lcdt_driver}
	Components/rtl8211/rtl8211.c
	)

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})
