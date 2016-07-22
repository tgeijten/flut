if (MSVC)
source_group("flut" FILES ${FLUT_SOURCES})
source_group("flut\\math" FILES ${FLUT_MATH_SOURCES})
source_group("flut\\buffer" FILES ${FLUT_BUFFER_SOURCES})
source_group("flut\\system" FILES ${FLUT_SYSTEM_SOURCES})
endif()

include_directories(${FLUT_INCLUDE_DIR})
target_compile_definitions( flut PRIVATE FLUT_EXPORTS )

set_target_properties(flut PROPERTIES 
	PROJECT_LABEL "flut"
	OUTPUT_NAME flut
    FOLDER "flut" # Place target inside a flut folder in MSVC
	)
