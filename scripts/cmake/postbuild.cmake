# Post build commands
#########################################################################################

### Create output with image sizes ###
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)

### Create binary from elf file ###
# PROJECT_OS_USE_TOUCHGFX_LIB : 0 : TouchGFX lib is not compiled
# PROJECT_OS_USE_TOUCHGFX_LIB : 1 : TouchGFX lib is compiled, separate image into binary and assets
#if("${PROJECT_OS_USE_TOUCHGFX_LIB}" STREQUAL "0")
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ARM_NONE_EABI_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMENT "Generate flat binary from .elf file")
#endif()
#if("${PROJECT_OS_USE_TOUCHGFX_LIB}" STREQUAL "1")
#	# .full.bin contains image and assets in one binary, could be used for linear programming if needed
#	# .bin is just the executable image without assets 
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ARM_NONE_EABI_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.full.bin COMMENT "Generate full binary from .elf file with code and assets")
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ARM_NONE_EABI_OBJCOPY} -O binary --remove-section=ExtFlashSection --remove-section=FontFlashSection --remove-section=TextFlashSection ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin COMMENT "Generate exe binary from .elf file")
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ARM_NONE_EABI_OBJCOPY} -O ihex --only-section=FontFlashSection --only-section=TextFlashSection --only-section=ExtFlashSection ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.touchgfx_assets.hex COMMENT "Generate assets .hex from .elf file")
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ARM_NONE_EABI_OBJCOPY} -O binary --only-section=FontFlashSection --only-section=TextFlashSection --only-section=ExtFlashSection ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.touchgfx_assets.bin COMMENT "Generate assets .bin from .elf file")
#	add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_update_touchgfx_asset_image.${ASG_EVO_SCRIPT_EXT} ${DEPLOY_FOLDER} ${CMAKE_PROJECT_NAME} ${ASG_EVO_TCS_PATH}/romfs ${FILE_NAME_UPDATE_LIST})
#endif()

### Generate stackusage overview, currently disabled due to recursive calls
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_stackusage.${ASG_EVO_SCRIPT_EXT} ${ASG_EVO_SCRIPT_PATH} ${TOOLCHAIN_DIR} ${CMAKE_PROJECT_NAME} COMMENT "Generating Stackusage overview")

### Call signing of binary file ###
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_sign_image.${ASG_EVO_SCRIPT_EXT} unused ${STM_CUBE_PROGRAMMER_DIR} ${CMAKE_PROJECT_NAME} COMMENT "Signing binary executable image")

### Combine FSBL bootloader with FSBL asset list ###
#if("${PROJECT_PROG_TYPE}" STREQUAL "FSBL" AND "${PROJECT_OS_TYPE}" STREQUAL "THREADX")
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_combine_FSBL_with_assets.${ASG_EVO_SCRIPT_EXT} ${CMAKE_PROJECT_NAME}.trusted.bin ${ASG_EVO_FSBL_ASSETS_GENERATED_PATH}/FSBL_assets.bin ${CMAKE_PROJECT_NAME}.trusted.flash.bin ${ASG_EVO_TCS_PATH}/tcsglobal/system_constants.h COMMENT "Combine FSBL image with FSBL asset list")
#endif()

### Copy binary files to deploy folder ###
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_deploy.${ASG_EVO_SCRIPT_EXT} ${DEPLOY_FOLDER} ${CMAKE_PROJECT_NAME} ${PROJECT_PROG_TYPE} ${FILE_NAME_UPDATE_LIST})

### Create ROM file system ###
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_update_tcs_romfs_image.${ASG_EVO_SCRIPT_EXT} ${DEPLOY_FOLDER} ${ASG_EVO_TCS_PATH}/romfs ${FILE_NAME_UPDATE_LIST})

### Copy script to start local FTP server in deploy folder (just for convinience) ###
#add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${ASG_EVO_SCRIPT_CMD_EXEC}/post_build_copy_ftpsrv_upload_script.${ASG_EVO_SCRIPT_EXT} ${DEPLOY_FOLDER} ${ASG_EVO_SCRIPT_PATH} ${ASG_EVO_DEV_FTP_USER}:${ASG_EVO_DEV_FTP_PASS}@${ASG_EVO_DEV_FTP_SERVER_IP})
