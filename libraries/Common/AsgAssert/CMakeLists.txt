message(STATUS "------------------------- AsgAssert ------------------------------------")

##### Name of Library #####
set(library_name lb_asgassert)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes 
	${ASG_EVO_LIBRARY_PATH}/Common
	# Middleware
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
)

if("${PROJECT_OS_TYPE}" STREQUAL "THREADX")

set (LIB_SOURCES
	AsgAssert.c
	)

elseif("${PROJECT_OS_TYPE}" STREQUAL "NOOS")

set (LIB_SOURCES
	AsgAssert_Noos.c
	)

endif()

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions( ${library_name} PRIVATE ${additional_defines})
target_link_libraries(${library_name} PUBLIC lb_syslayer)
