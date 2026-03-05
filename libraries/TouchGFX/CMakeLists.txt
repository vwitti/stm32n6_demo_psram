message(STATUS "------------------------- TouchGFX -------------------------")

##### Name of Library #####
set(library_name lb_touchgfx)

##### Additional Defines for library #####
set(additional_defines 

)

set_source_files_properties(
  ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/HardwareMJPEGDecoder.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/target/generated/OSWrappers.cpp
  COMPILE_FLAGS "-Wno-volatile"
)

message(WARNING "-------------------------------------------------------------------------------------")
message(WARNING "Following option are disabled for test purposes. Resolve later for Releases")
message(WARNING "-Wno-error=volatile")
message(WARNING "-------------------------------------------------------------------------------------")


##### Additional Includes for library #####
set(additional_includes
	# BSP
	BSP/${PROJECT_BOARD_TYPE}/BSP/APPLI
	# STM32 HAL Layer
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc
	${ASG_EVO_LIBRARY_PATH}/Drivers/STM32N6xx_HAL_Driver/Inc/Legacy
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Device/ST/STM32N6xx/Include
	${ASG_EVO_LIBRARY_PATH}/Drivers/CMSIS/Include
	# ThreadX includes
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
    # touch gfx intern
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/touchgfx/framework/include
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/touchgfx/framework/include/touchgfx/hal
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/gui/include
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/generated/gui_generated/include
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/generated/texts/include
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/generated/fonts/include
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/generated/videos/include
    ${ASG_EVO_TCS_PATH}/touchgfx/TouchGFX/generated/images/include
    ${CMAKE_CURRENT_SOURCE_DIR}/target/generated
    ${CMAKE_CURRENT_SOURCE_DIR}/target
)

##########TOUCHGFX_TARGET_RESOURCES_BEGIN##########
set (LIB_SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/STM32DMA.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/OSWrappers.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/TouchGFXConfiguration.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/HardwareMJPEGDecoder.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/TouchGFXGeneratedHAL.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/TouchGFXGPIO.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/TouchGFXHAL.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/KeySampler.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/STM32TouchController.cpp
${CMAKE_CURRENT_SOURCE_DIR}/target/CortexMMCUInstrumentation.cpp
${CMAKE_CURRENT_SOURCE_DIR}/App/app_touchgfx.c
${CMAKE_CURRENT_SOURCE_DIR}/target/generated/nema_hal.c
)
##########TOUCHGFX_TARGET_RESOURCES_END##########

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})

