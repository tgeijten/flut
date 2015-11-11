set (TEST_FILES test.cpp)
file (GLOB SCONE_FILES "scone/*.h" "scone/*.cpp")
file (GLOB FLUT_SOURCES "../flut/*.hpp")
file (GLOB FLUT_MATH_SOURCES "../flut/math/*.hpp")
file (GLOB FLUT_STORAGE_SOURCES "../flut/storage/*.hpp")
file (GLOB FLUT_SYSTEM_SOURCES "../flut/system/*.hpp")

source_group("" FILES ${TEST_FILES})
source_group("scone" FILES ${SCONE_FILES})
source_group("flut" FILES ${FLUT_SOURCES})
source_group("flut\\math" FILES ${FLUT_MATH_SOURCES})
source_group("flut\\storage" FILES ${FLUT_STORAGE_SOURCES})
source_group("flut\\system" FILES ${FLUT_SYSTEM_SOURCES})

include_directories("../")

add_executable(test ${TEST_FILES} ${SCONE_FILES} ${FLUT_SOURCES} ${FLUT_MATH_SOURCES} ${FLUT_STORAGE_SOURCES} ${FLUT_SYSTEM_SOURCES})

set_target_properties(test PROPERTIES PROJECT_LABEL "test" OUTPUT_NAME test)	
