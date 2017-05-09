# Gather flut sources.
file (GLOB FLUT_SOURCES "*.hpp" "*.cpp")
file (GLOB FLUT_MATH_SOURCES "math/*.hpp" "math/*.cpp")
file (GLOB FLUT_BUFFER_SOURCES "buffer/*.hpp" "buffer/*.cpp")
file (GLOB FLUT_SYSTEM_SOURCES "system/*.hpp" "system/*.cpp")
file (GLOB FLUT_OPT_SOURCES "optimization/*.hpp" "optimization/*.cpp")

add_library(flut SHARED ${FLUT_SOURCES} ${FLUT_MATH_SOURCES} ${FLUT_BUFFER_SOURCES} ${FLUT_SYSTEM_SOURCES} ${FLUT_OPT_SOURCES})

if (UNIX)
    target_link_libraries(flut pthread)
endif()

if (MSVC)
source_group("flut" FILES ${FLUT_SOURCES})
source_group("flut\\buffer" FILES ${FLUT_BUFFER_SOURCES})
source_group("flut\\math" FILES ${FLUT_MATH_SOURCES})
source_group("flut\\optimization" FILES ${FLUT_OPT_SOURCES})
source_group("flut\\system" FILES ${FLUT_SYSTEM_SOURCES})
endif()

include_directories(${FLUT_INCLUDE_DIR})

target_compile_definitions( flut PRIVATE FLUT_EXPORTS )

set_target_properties(flut PROPERTIES 
	PROJECT_LABEL "flut"
	OUTPUT_NAME flut
    FOLDER "flut" # Place target inside a flut folder in MSVC
	)
