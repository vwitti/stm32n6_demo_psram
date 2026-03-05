message(STATUS "------------------------- STM32_ExtMem_Manager -------------------------")

##### Name of Library #####
set(library_name lb_stm32_extmem_mm)

##### Additional Defines for library #####
set(additional_defines 
	
)

message(WARNING "-------------------------------------------------------------------------------------")
message(WARNING "Following option are disabled for test purposes. Resolve later for Releases")
message(WARNING "-Wno-error=maybe-uninitialized")
message(WARNING "-------------------------------------------------------------------------------------")
add_compile_options(-Wno-error=maybe-uninitialized)

##### Additional Includes for library #####
set(additional_includes 
    # Include to config file
    ${ASG_EVO_PROJECT_PATH}/Common/Inc/Init/extmem
    
	# STM32 HAL Layer
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Device/ST/STM32N6xx/Include
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Include
	# Middleware
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager/custom
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/STM32_ExtMem_Manager/custom/memories
)

set (LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32_extmem.c
    ${CMAKE_CURRENT_SOURCE_DIR}/boot/stm32_boot_xip.c
    ${CMAKE_CURRENT_SOURCE_DIR}/custom/stm32_custom_driver.c
)

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})

