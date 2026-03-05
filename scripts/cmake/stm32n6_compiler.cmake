add_compile_definitions (${PROJECT_DEFINES} ${ASG_EVO_Defines_Syms})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
# -mcmse  : Cortex Security Extensions
# -mthumb : Thumb extensions
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} ${PROJECT_EXTRA_C_FLAGS} -mcmse -mthumb -Wall -Werror ")
set (CMAKE_CXX_FLAGS "${MCPU} -std=c++20 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} ${PROJECT_EXTRA_CPP_FLAGS} -mcmse -mthumb -Wall -Werror ")
# We are in the Debug/Release folder, so we need to go back one path more
# -u _printf_float
# -lstdc++ -lsupc++
set (CMAKE_EXE_LINKER_FLAGS "-T../${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group -u _printf_float")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
