# This file was generated using the 4DIAC FORTE Export Filter 3.0.0.202601211617!

target_sources(forte-ASGEVO_PACKAGE PRIVATE
        SFB_ASGEVO_SET_CA_VALVES_fbt.cpp
        SFB_ASGEVO_GET_LEG_PRESSURE_fbt.cpp
        LAS_GLOBAL_CONST_gcf.cpp
        SFB_ASGEVO_CONTROL_fbt.cpp
        SFB_ASGEVO_GET_RAM_STROKE_fbt.cpp
        SFB_ASGEVO_LAS_SIGNALS_fbt.cpp
        SFB_ASGEVO_SET_STD_VALVES_fbt.cpp
        events.c
        FacePara.c
        sensors.c
        SensorSimulation.c
        ShieldPara.c
        valves.c
        4diac/iosubsystem_thread_posix.c
        4diac/kv11.c
        4diac/kv11_client.c
)
add_subdirectory(FB)
add_subdirectory(MUX)