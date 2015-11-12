file (GLOB FLUT_SOURCES "*.hpp")
file (GLOB FLUT_MATH_SOURCES "math/*.hpp")
file (GLOB FLUT_STORAGE_SOURCES "storage/*.hpp")
file (GLOB FLUT_SYSTEM_SOURCES "system/*.hpp" "system/*.cpp")

source_group("flut" FILES ${FLUT_SOURCES})
source_group("flut\\math" FILES ${FLUT_MATH_SOURCES})
source_group("flut\\storage" FILES ${FLUT_STORAGE_SOURCES})
source_group("flut\\system" FILES ${FLUT_SYSTEM_SOURCES})

add_library(flut SHARED ${FLUT_SOURCES} ${FLUT_MATH_SOURCES} ${FLUT_STORAGE_SOURCES} ${FLUT_SYSTEM_SOURCES})
set_target_properties(flut PROPERTIES 
	DEFINE_SYMBOL FLUT_EXPORTS 
	PROJECT_LABEL "flut"
	OUTPUT_NAME flut)
