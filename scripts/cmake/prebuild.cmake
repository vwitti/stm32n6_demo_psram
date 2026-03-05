# Pre build commands
#########################################################################################

set (ASG_EVO_FSBL_ASSETS_PATH				"${ASG_EVO_TCS_PATH}/FSBL_Assets")
set (ASG_EVO_FSBL_ASSETS_GENERATED_PATH		"${ASG_EVO_TCS_PATH}/FSBL_Assets/generated")

set (ASG_EVO_APPLI_TOUCHGFX_PATH        	"${ASG_EVO_TCS_PATH}/touchgfx")
set (ASG_EVO_APPLI_TOUCHGFX_GENERATED_PATH	"${ASG_EVO_TCS_PATH}/touchgfx/generated")

###### Create FSBL Assets ######
if("${PROJECT_PROG_TYPE}" STREQUAL "FSBL" AND "${PROJECT_OS_TYPE}" STREQUAL "THREADX")

# Path is not part of repo --> so generate dynamically
file(MAKE_DIRECTORY "${ASG_EVO_FSBL_ASSETS_GENERATED_PATH}")

add_custom_command(
  OUTPUT ${ASG_EVO_FSBL_ASSETS_PATH}/generated/FSBL_assets.h
  COMMAND ${ASG_EVO_FSBL_ASSETS_PATH}/create_bin_assets.sh -l ${ASG_EVO_FSBL_ASSETS_PATH}/assetlist.txt -o ${ASG_EVO_FSBL_ASSETS_GENERATED_PATH}/FSBL_assets.bin -H ${ASG_EVO_FSBL_ASSETS_GENERATED_PATH}/FSBL_assets.h

  DEPENDS ${ASG_EVO_FSBL_ASSETS_PATH}/create_bin_assets.sh ${ASG_EVO_FSBL_ASSETS_PATH}/assetlist.txt
  COMMENT "Create FSBL bootloader assets"
)
add_custom_target(precompile_FSBL_Assets ALL
  DEPENDS ${ASG_EVO_FSBL_ASSETS_GENERATED_PATH}/FSBL_assets.h
)
add_dependencies(${CMAKE_PROJECT_NAME} precompile_FSBL_Assets)

endif()
####################################
