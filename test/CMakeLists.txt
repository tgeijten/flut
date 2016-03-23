file (GLOB TEST_FILES "*.h" "*.cpp")
file (GLOB SCONE_FILES "scone/*.h" "scone/*.cpp")

source_group("" FILES ${TEST_FILES})
source_group("scone" FILES ${SCONE_FILES})

include_directories("../")

add_executable(flut_test ${TEST_FILES} ${SCONE_FILES})

include_directories(${FLUT_INCLUDE_DIR})

#target_link_libraries(flut_test flut)

set_target_properties(flut_test	PROPERTIES
	PROJECT_LABEL "flut_test"
	OUTPUT_NAME flut_test
    FOLDER "flut" # Place target inside a flut folder in MSVC
	)
