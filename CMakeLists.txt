cmake_minimum_required(VERSION 2.8.11)
# 2.8.11 is required for how we use Qt5.

project(flut)

# To create a folder hierarchy within Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_path(FLUT_INCLUDE_DIR
    NAMES flut/system/types.hpp
	PATHS ${CMAKE_CURRENT_SOURCE_DIR}
	)

# Compiler flags.
# ---------------
# Must compile with C++11 with gcc/clang.
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR
   ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    if(APPLE)
        if(XCODE)
            set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++11")
            set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
        else()
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
            if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
            endif()
        endif()
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    endif()
endif()
	
# Place build products (libraries, executables) in root
# binary (build) directory. Otherwise, they get scattered around
# the build directory and so the dll's aren't next to the executables.
get_filename_component(CONFIG_NAME "${CMAKE_BINARY_DIR}" NAME)
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}")
set(LIBRARY_OUTPUT_PATH "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}")

# Gather flut sources.
file (GLOB FLUT_SOURCES "flut/*.hpp" "flut/*.cpp")
file (GLOB FLUT_MATH_SOURCES "flut/math/*.hpp" "flut/math/*.cpp")
file (GLOB FLUT_BUFFER_SOURCES "buffer/*.hpp" "flut/buffer/*.cpp")
file (GLOB FLUT_SYSTEM_SOURCES "flut/system/*.hpp" "flut/system/*.cpp")
add_library(flut SHARED ${FLUT_SOURCES} ${FLUT_MATH_SOURCES} ${FLUT_BUFFER_SOURCES} ${FLUT_SYSTEM_SOURCES})

# Process source code.
add_subdirectory(test)
add_subdirectory(flut)

enable_testing()
add_test(flut_test "${CMAKE_SOURCE_DIR}/bin/${CONFIG_NAME}/flut_test")
