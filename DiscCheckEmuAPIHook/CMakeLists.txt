﻿project (DCEAPIHook) 

include(../cmake/Detours.cmake)

CPMAddPackage("gh:jbeder/yaml-cpp#0.8.0")

add_library (${PROJECT_NAME} SHARED
"APIHook.cpp"
"Config/ConfigParser.cpp"
"Res/Resources.rc"
"Util/StringUtils.cpp"
"Util/RegUtils.cpp"
)

target_link_libraries(${PROJECT_NAME} PRIVATE detours yaml-cpp winmm.lib)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

target_compile_options(${PROJECT_NAME} PRIVATE /W4)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
	target_compile_options(${PROJECT_NAME} PRIVATE /WX)
endif()