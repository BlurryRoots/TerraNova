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

# glm
include_directories (lib/glm)

# stb image loader
include_directories (lib/stb)

# glew
add_definitions (-DGLEW_STATIC)
option (glew-cmake_BUILD_SHARED "" OFF)
add_subdirectory (lib/glew)
set (GLEW_INCLUDE_DIR lib/glew/include lib/glew/src)
set (GLEW_LIBRARY libglew_static)
# add glew includes
include_directories (${GLEW_INCLUDE_DIR})

# sdl2
#add_definitions (-DSDL_STATIC)
#add_definitions (-DSDL_SHARED)
#option (SDL_SHARED "" ON)
#option (SDL_STATIC "" OFF)
#add_subdirectory (sdl2)

## sdl2
find_package (SDL2 REQUIRED)
message (STATUS
	"Found SDL2 on system:\n"
	"inc: ${SDL2_INCLUDE_DIR}\n"
	"lib: ${SDL2_LIBRARY}"
)
# add sdl2 includes
include_directories (${SDL2_INCLUDE_DIR})

# tiny obj (file) loader
add_library (tinyobjloader STATIC
	lib/tinyobjloader/tiny_obj_loader.h
	lib/tinyobjloader/tiny_obj_loader.cc
)
set (TINYOBJ_LIBRARY tinyobjloader)
set (TINYOBJ_INCLUDE_DIR lib/tinyobjloader)
# add tinyobjloader includes
include_directories (${TINYOBJ_INCLUDE_DIR})

# yanecos
add_subdirectory (lib/yanecos)
set (YANECOS_INCLUDE_DIR lib/yanecos/inc)
# add yanecos includes
include_directories (${YANECOS_INCLUDE_DIR})

# json
include_directories (lib/json/src)

# include custom includes
include_directories (inc)

# c++11 activation
list (APPEND CMAKE_CXX_FLAGS "-std=c++11")
# compilation flags
add_definitions (-Wall)

# main target
add_executable (${app_name} ${source_files})
target_link_libraries (
	${app_name}
	${SDL2_LIBRARY} ${TINYOBJ_LIBRARY} ${GLEW_LIBRARY} ${SYSTEM_LIBS}
)


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
