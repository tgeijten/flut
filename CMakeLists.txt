cmake_minimum_required(VERSION 2.8.11)
# 2.8.11 is required for how we use Qt5.

project(flut)

# To create a folder hierarchy within Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_path(FLUT_INCLUDE_DIR
    NAMES "flut/types.h"
    )

# Place build products (libraries, executables) in root
# binary (build) directory. Otherwise, they get scattered around
# the build directory and so the dll's aren't next to the executables.
get_filename_component(CONFIG_NAME "${CMAKE_BINARY_DIR}" NAME)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}")

# Process source code.
add_subdirectory(test)
if(MSVC)
    # Create a project for the header-only library (doesn't work outside
    # of MSVC).
    add_subdirectory(flut)
endif()

enable_testing()
add_test(flut_test "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}/test.exe")
