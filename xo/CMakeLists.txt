SET ( XO_LIB_NAMES algorithm container debug filesystem geometry numerical stream string system time utility )

foreach(xolib ${XO_LIB_NAMES})
  file(GLOB XO_${xolib} ${xolib}/*.hpp ${xolib}/*.cpp)
  list(APPEND XO_SOURCES ${XO_${xolib}})
endforeach()

add_library(flut SHARED ${XO_SOURCES} )

if (UNIX)
    target_link_libraries(flut pthread)
endif()

if (MSVC)
foreach(xolib ${XO_LIB_NAMES})
source_group("xo\\${xolib}" FILES ${XO_${xolib}} )
endforeach()
endif()

include_directories(${FLUT_INCLUDE_DIR})

target_compile_definitions( flut PRIVATE XO_EXPORTS )

set_target_properties(flut PROPERTIES 
	PROJECT_LABEL "flut"
	OUTPUT_NAME flut
    FOLDER "flut" # Place target inside a flut folder in MSVC
	)
