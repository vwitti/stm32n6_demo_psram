# This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!

target_sources(forte-ASGEVO_PACKAGE PUBLIC
        FILE_SET HEADERS
        FILES
        SFB_ASGEVO_SET_STD_VALVES_fbt.h
        SFB_ASGEVO_GET_RAM_STROKE_fbt.h
        SFB_ASGEVO_SET_CA_VALVES_fbt.h
        SFB_ASGEVO_GET_LEG_PRESSURE_fbt.h
        SFB_ASGEVO_CONTROL_fbt.h
        LAS_GLOBAL_CONST_gcf.h
        SFB_ASGEVO_LAS_SIGNALS_fbt.h
)
add_subdirectory(MUX)
add_subdirectory(FB)