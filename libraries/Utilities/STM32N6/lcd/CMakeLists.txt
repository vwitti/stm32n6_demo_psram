message(STATUS "------------------------- Utilities STM32 LCD -------------------------")

##### Name of Library #####
set(library_name lb_utils_stm32n6)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes 
	${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK/Components/Common
	${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK
)

set (LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32_lcd.c
	)


add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})
