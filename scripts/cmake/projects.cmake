# CMake project specific definition for STM32CubeIDE
#########################################################################################

########## Global pathes ##########
set (ASG_EVO_GCC_VERSION "14.3.1")
set (STM_CUBE_PROGRAMMER_DIR "$ENV{USER_STM_CUBE_PROGRAMMER_DIR}")
set (DEPLOY_FOLDER "$ENV{USER_DEPLOY_FOLDER}")
set (USER_ASG_EVO_COMPILER_PATH "$ENV{USER_ASG_EVO_COMPILER_PATH}")
set (USER_IP_CONFIG_FILE "$ENV{USER_IP_CONFIG_FILE}")
message(STATUS "STM_CUBE_PROGRAMMER_DIR    = ${STM_CUBE_PROGRAMMER_DIR}")
message(STATUS "DEPLOY_FOLDER              = ${DEPLOY_FOLDER}")
message(STATUS "USER_ASG_EVO_COMPILER_PATH = ${USER_ASG_EVO_COMPILER_PATH}")
message(STATUS "USER_IP_CONFIG_FILE        = ${USER_IP_CONFIG_FILE}")

### Check if we use the same compiler installation ###
get_filename_component(TOOLCHAIN_BIN_DIR "${CMAKE_C_COMPILER}" DIRECTORY)
if (NOT ${USER_ASG_EVO_COMPILER_PATH} STREQUAL "")
	message(STATUS "Variable ${USER_ASG_EVO_COMPILER_PATH} set. Verify we have exactly this toolchain is path")
	if (NOT ${USER_ASG_EVO_COMPILER_PATH} STREQUAL ${TOOLCHAIN_BIN_DIR})
	    message(STATUS "!!!Toolchain mismatch!!!")
	    message(STATUS "-------------------------------------------------------------------------------------")
	    message(STATUS "ASG-EVO expects GCC toolchain in ${USER_ASG_EVO_COMPILER_PATH}")
	    message(STATUS "Actual toolchain path is ${TOOLCHAIN_BIN_DIR}")
	    message(STATUS "-------------------------------------------------------------------------------------")
	    message(FATAL_ERROR)
	endif()
else()
	message(STATUS "Variable ${USER_ASG_EVO_COMPILER_PATH} not set. Assuming we are running from STMCubeIDE")
endif()

### Needed to create binary from .elf file ###
set(ARM_NONE_EABI_OBJCOPY "${TOOLCHAIN_BIN_DIR}/arm-none-eabi-objcopy")


########## relative pathes ##########
set (ASG_EVO_PROJECT_PATH   "${CMAKE_CURRENT_SOURCE_DIR}")
set (ASG_EVO_BSP_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/BSP")
set (ASG_EVO_LIBRARY_PATH   "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set (ASG_EVO_SCRIPT_PATH    "${CMAKE_CURRENT_SOURCE_DIR}/scripts")
set (ASG_EVO_TCS_PATH       "${CMAKE_CURRENT_SOURCE_DIR}/tcs")

########## Verify GCC toolchain ########## 
if (NOT ${CMAKE_C_COMPILER_VERSION} STREQUAL ${ASG_EVO_GCC_VERSION})
    message(STATUS "!!!Version mismatch!!!")
    message(STATUS "-------------------------------------------------------------------------------------")
    message(STATUS "ASG-EVO expects GCC version ${ASG_EVO_GCC_VERSION}")
    message(STATUS "Your toolchain is version ${CMAKE_C_COMPILER_VERSION}")
    message(STATUS "-------------------------------------------------------------------------------------")
    message(FATAL_ERROR)
endif()
if (NOT ${CMAKE_CXX_COMPILER_VERSION} STREQUAL ${ASG_EVO_GCC_VERSION})
    message(STATUS "!!!Version mismatch!!!")
    message(STATUS "-------------------------------------------------------------------------------------")
    message(STATUS "ASG-EVO expects GCC version ${ASG_EVO_GCC_VERSION}")
    message(STATUS "Your toolchain is version ${CMAKE_CXX_COMPILER_VERSION}")
    message(STATUS "-------------------------------------------------------------------------------------")
    message(FATAL_ERROR)
endif()

########## Verify host platform ##########
if(CMAKE_HOST_WIN32)
    message(STATUS "-------------------------------- WIN32 ---------------------------------")
    message(STATUS "You love your windows, but no support here!")
    message(STATUS "Please use provided VM")
	message(FATAL_ERROR)
endif()

if(CMAKE_HOST_UNIX)
    message(STATUS "-------------------------------- LINUX ---------------------------------")
    set (TOOLCHAIN_DIR unused)
    set (ASG_EVO_SCRIPT_EXT sh)
    set (ASG_EVO_SCRIPT_CMD_EXEC ${ASG_EVO_SCRIPT_PATH})
    set (FILE_NAME_UPDATE_LIST update_list.txt)
endif()

#####################################################################
################################# Allgemeine Build Infos ############
##################################################################### 
execute_process(
    COMMAND git branch --show-current
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE BUILD_INFO_GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git describe --always --dirty --abbrev=10
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE BUILD_INFO_GIT_HASH_FIRST10
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

### Version and TimeStamp Handling ###
string(TIMESTAMP BUILD_INFO_DATE "%Y-%m-%d")
string(TIMESTAMP BUILD_INFO_TIME "%H:%M:%S")
add_definitions(-DBUILD_INFO_GIT_BRANCH=\"${BUILD_INFO_GIT_BRANCH}\")
add_definitions(-DBUILD_INFO_GIT_HASH_FIRST10=\"${BUILD_INFO_GIT_HASH_FIRST10}\")
add_definitions(-DBUILD_INFO_DATE=\"${BUILD_INFO_DATE}\")
add_definitions(-DBUILD_INFO_TIME=\"${BUILD_INFO_TIME}\")
add_definitions(-DPROJECT_BUILD_NAME=\"${PROJECT_BUILD_NAME}\")
### IP Configuration ###
add_definitions(-DUSER_IP_CONFIG_FILE=\"${USER_IP_CONFIG_FILE}\")
add_definitions(-DFILE_NAME_UPDATE_LIST=\"${FILE_NAME_UPDATE_LIST}\")
### Pther System configuration ###
add_definitions(-DPROJECT_STM32CUBE_BUG_WORKAROUNDS=${PROJECT_STM32CUBE_BUG_WORKAROUNDS})

#####################################################################
############################# CPU Flags #############################
#####################################################################

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33				  "-mcpu=cortex-m33")
set (MCPU_CORTEX_M55				  "-mcpu=cortex-m55")
set (MCPU_CORTEX_M85				  "-mcpu=cortex-m85")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV4                        "-mfpu=vfpv4")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################
###################### VARIABLES ######################################
set (PROJECT_TYPE             "exe")
#set (LINKER_SCRIPT            "../STM32N657XX_AXISRAM2_fsbl.ld")
set (MCPU                     "-mcpu=cortex-m55")

# Hard FPU (Instructions)
set(MFPU "-mfpu=fpv5-d16")
set(MFLOAT_ABI "-mfloat-abi=hard")

# SoftFP (wenn du keine Hard-Float Libraries hast)
#set(MFPU "-mfpu=fpv5-sp-d16")
#set(MFLOAT_ABI "-mfloat-abi=softfp")
#Soft FPU
#set(MFPU "")
#set(MFLOAT_ABI "-mfloat-abi=soft")

set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")
# -ffunction-sections : Each function is moved to a separate section (saves memory)
# -fstack-usage       : Generate .su files for stack analysis
set (PROJECT_EXTRA_C_FLAGS    "-fcallgraph-info -fstack-usage -ffunction-sections")
set (PROJECT_EXTRA_CPP_FLAGS    "-fcallgraph-info -fstack-usage -ffunction-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit  -femit-class-debug-always")

# -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit  -femit-class-debug-always  -mcmse -MMD -MP
#-ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -femit-class-debug-always -fstack-usage -fcyclomatic-complexity -mcmse -MMD -MP
