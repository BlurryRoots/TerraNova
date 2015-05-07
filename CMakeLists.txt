cmake_minimum_required (VERSION 2.8)

# project setup
#

project (TerraNova)
set (app_name TerraNova)

# includes cmake extension scripts
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# check for in-tree build attempt
#
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message (FATAL_ERROR
		"Prevented in-tree built.\n"
		"Please create a seperate build directory,\n"
		"outsite of root directory and call:\n"
		"cmake PATH_TO_TERRA_NOVA (e.g ../)"
	)
endif ()

# build setup
#

# put the executable into the bin directory
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set (ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# find every source file
file (GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*)


# system libraries
set (SYSTEM_LIBS)
list (APPEND SYSTEM_LIBS z)
list (APPEND SYSTEM_LIBS pthread)

# library / modules
add_subdirectory (lib)

# sdl2
#include_directories (lib/sdl2/include build/sdl2/include)
#set (SDL2_LIBRARY SDL2-static)

# glew
include_directories (lib/glew/include lib/glew/src)
set (GLEW libglew_static)

## sdl2
find_package (SDL2 REQUIRED)
message (STATUS
	"Found SDL2 on system:\n"
	"inc: ${SDL2_INCLUDE_DIR}\n"
	"lib: ${SDL2_LIBRARY}"
)
include_directories (${SDL2_INCLUDE_DIR})

# include custom includes
include_directories (inc)

# c++11 activation
list (APPEND CMAKE_CXX_FLAGS "-std=c++11")
# compilation flags
add_definitions (-Wall)

# main target
add_executable (${app_name} ${source_files})
target_link_libraries (${app_name} ${SDL2_LIBRARY} ${GLEW} ${SYSTEM_LIBS})
#target_link_libraries (${app_name} ${SDL2_LIBRARY} ${GLEW})


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

