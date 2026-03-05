message(STATUS "------------------------- Syslog ---------------------------------------")

##### Name of Library #####
set(library_name lb_syslog)

##### Additional Defines for library #####
set(additional_defines 

)

##### Additional Includes for library #####
set(additional_includes
    ${ASG_EVO_TCS_PATH}
	${ASG_EVO_LIBRARY_PATH}/Common
	# Middleware
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST
	${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/threadx/ports/cortex_m55/gnu/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/common/inc
    ${ASG_EVO_LIBRARY_PATH}/Middlewares/ST/netxduo/ports/cortex_m55/gnu/inc
)


set (LIB_SOURCES
	SysLog.c
	)

add_library(${library_name} ${LIB_SOURCES})
target_include_directories( ${library_name} PRIVATE ${additional_includes})
target_compile_definitions(${library_name} PRIVATE ${additional_defines})

