# Install script for directory: /home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/volker/.eclipse/com.st.stm32cube.ide.mcu.rcp.product_2.0.0_1934254364_linux_gtk_x86_64/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.14.3.rel1.linux64_1.0.0.202510151430/tools/bin/arm-none-eabi-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Common/AsgAssert/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Common/BSP_N6570-DK/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Common/SysLayer/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Common/SysLog/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Common/Utils/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Middlewares/ST/threadx/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Middlewares/ST/netxduo/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Middlewares/ST/filex/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Middlewares/ST/STM32_ExtMem_Manager/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/libraries/Utilities/STM32N6/lcd/cmake_install.cmake")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/volker/tiefenbach/repos/git/ASG-EVO/N6570_DK/N6570_EVAL.FSBL/Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
