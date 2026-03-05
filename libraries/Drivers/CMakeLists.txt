message(STATUS "------------------------- STM32N6 Driver Layer -------------------------")

##### Name of Library #####
set(library_name lb_stm32n6drv)

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
    STM32N6xx_HAL_Driver/Inc
    STM32N6xx_HAL_Driver/Inc/Legacy
    CMSIS/Device/ST/STM32N6xx/Include
    CMSIS/Include
)

set (LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_bsec.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_cortex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_crc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_crc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_dma.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_dma2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_dma_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_eth.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_eth_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_exti.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_fdcan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_gpio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_gpu2d.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_i2c.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_i2c_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_icache.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_jpeg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_ltdc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_ltdc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_mmc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_mmc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_pwr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_pwr_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_ramcfg.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rcc.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rcc_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_rif.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_sd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_sd_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_spi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_spi_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_tim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_tim_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_uart.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_uart_ex.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_hal_xspi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32N6xx_HAL_Driver/Src/stm32n6xx_ll_sdmmc.c
	)

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})
