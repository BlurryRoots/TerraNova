cmake_minimum_required (VERSION 2.8)

project (TerraNova)

set (app_name TerraNova)

# includes cmake/FindSDL2.cmake
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# put the executable into the bin directory
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# find every source file
file (GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*)

#
find_package (SDL2 REQUIRED)
include_directories (${SDL2_INCLUDE_DIR})


# c++11 activation
list (APPEND CMAKE_CXX_FLAGS "-std=c++11")
# compilation flags
add_definitions (-Wall)

# main target
add_executable (${app_name} ${source_files})
target_link_libraries (${app_name} ${SDL2_LIBRARY})


# command to copy resources when using default target
add_custom_target (assets
	COMMAND cp -r "${PROJECT_SOURCE_DIR}/res/*" $<TARGET_FILE_DIR:${app_name}>
	DEPENDS ${app_name}
)

# 'make run' execute main into the bin directory
add_custom_target (run
	COMMAND ${EXECUTABLE_OUTPUT_PATH}/${app_name}
		DEPENDS assets
		WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)

