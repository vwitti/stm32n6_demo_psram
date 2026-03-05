#############################################################################
# Copyright (c) 2025 Martin Erich Jobst
#
# This program and the accompanying materials are made available under the
# terms of the Eclipse Public License 2.0 which is available at
# http://www.eclipse.org/legal/epl-2.0.
#
# SPDX-License-Identifier: EPL-2.0
#
# Contributors:
#    Martin Erich Jobst
#      - initial API and implementation and/or initial documentation
#############################################################################

add_library(forte-ASGEVO_PACKAGE)
target_include_directories(forte-ASGEVO_PACKAGE PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/../modules/IEC61131-3/include
${CMAKE_CURRENT_SOURCE_DIR}/../modules/utils/include
${CMAKE_CURRENT_SOURCE_DIR}/../stdfblib/events/include
)
target_link_libraries(forte-ASGEVO_PACKAGE PUBLIC forte-core)
target_link_libraries(forte PUBLIC $<IF:$<BOOL:${BUILD_SHARED_LIBS}>,forte-ASGEVO_PACKAGE,$<LINK_LIBRARY:WHOLE_ARCHIVE,forte-ASGEVO_PACKAGE>>)

add_subdirectory(include)
add_subdirectory(src)

install(TARGETS forte-ASGEVO_PACKAGE EXPORT forte-export FILE_SET HEADERS)
