file (GLOB FLUT_SOURCES "*.hpp")
file (GLOB FLUT_MATH_SOURCES "math/*.hpp")
file (GLOB FLUT_BUFFER_SOURCES "buffer/*.hpp")
file (GLOB FLUT_SYSTEM_SOURCES "system/*.hpp")

source_group("flut" FILES ${FLUT_SOURCES})
source_group("flut\\math" FILES ${FLUT_MATH_SOURCES})
source_group("flut\\buffer" FILES ${FLUT_BUFFER_SOURCES})
source_group("flut\\system" FILES ${FLUT_SYSTEM_SOURCES})

add_library(flut STATIC ${FLUT_SOURCES} ${FLUT_MATH_SOURCES} ${FLUT_BUFFER_SOURCES} ${FLUT_SYSTEM_SOURCES})

include_directories(${FLUT_INCLUDE_DIR})

set_target_properties(flut PROPERTIES LINKER_LANGUAGE CXX)

set_target_properties(flut PROPERTIES 
	DEFINE_SYMBOL FLUT_EXPORTS 
	PROJECT_LABEL "flut"
	OUTPUT_NAME flut
    FOLDER "flut" # Place target inside a flut folder in MSVC
	)
