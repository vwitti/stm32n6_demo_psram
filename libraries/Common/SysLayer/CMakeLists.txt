message(STATUS "------------------------- HalBoard -------------------------------------")

##### Name of Library #####
set(library_name lb_syslayer)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes
    ${ASG_EVO_TCS_PATH}
	${ASG_EVO_LIBRARY_PATH}/Common
	# STM32 HAL Layer
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Device/ST/STM32N6xx/Include
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Include
	# BSP Layer
	${ASG_EVO_LIBRARY_PATH}/Common/BSP_N6570-DK
	# Middleware Layer
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
)

if("${PROJECT_OS_TYPE}" STREQUAL "THREADX")

set (LIB_SOURCES_TREADX
	HalThread.c
	)

endif()

set (LIB_SOURCES
	HalBoard.c
	HalSystemStop.c
	)

# Additional Defines for library
set(additional_defines 

)

add_library(${library_name} ${LIB_SOURCES} ${LIB_SOURCES_TREADX})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})
if("${PROJECT_OS_TYPE}" STREQUAL "THREADX")
	target_link_libraries(${library_name} PUBLIC lb_threadx)
endif()

