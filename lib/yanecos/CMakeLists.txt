cmake_minimum_required (VERSION 2.8)
project (yanecos)

# put the executable into the bin directory
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# c++11 activation
list (APPEND CMAKE_CXX_FLAGS "-std=c++11")

# compilation flags
add_definitions (-Wall)

# find every source file
file (GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*)

# build test executable
if (YANECOS_TESTS)
	# find every source file
	file (GLOB_RECURSE test_files ${PROJECT_SOURCE_DIR}/test/*)

	add_executable (test-all ${test_files})

	# 'make run' execute main into the bin directory
	add_custom_target (tests
		COMMAND ${EXECUTABLE_OUTPUT_PATH}/test-all -s
			DEPENDS test-all
			WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
	)
endif ()

# app specific includes
include_directories (inc)
include_directories (lib)
