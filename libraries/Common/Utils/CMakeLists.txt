message(STATUS "------------------------- Utils ----------------------------------------")

##### Name of Library #####
set(library_name lb_utils)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes 
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
)


if("${PROJECT_OS_TYPE}" STREQUAL "THREADX")

set (LIB_SOURCES_TREADX
	TxArray.c
	ip_utils.c
	)

endif()

set (LIB_SOURCES
	Sys_BuildInfo.c
	printf_utils.c
	kv_store.c
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

