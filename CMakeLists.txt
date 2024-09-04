cmake_minimum_required(VERSION 3.10)

project(capoo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if (MSVC)
    add_compile_options(/source-charset:utf-8 /execution-charset:utf-8 /wd4244 /wd4305 /wd4267)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wno-conversion -Wno-deprecated-declarations)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(THIRDPARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/3party)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
set(SFML_STATIC_LIBRARIES FALSE)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1  
)
FetchContent_MakeAvailable(SFML)
add_subdirectory(${THIRDPARTY_DIRECTORY}/jsoncpp-1.9.5)
add_subdirectory(${THIRDPARTY_DIRECTORY}/spine-sfml-4.1.x)

file(GLOB SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics jsoncpp spine-sfml)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy ALL Data"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_CURRENT_LIST_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Copy README.md"
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_LIST_DIR}/README.md $<TARGET_FILE_DIR:${PROJECT_NAME}>/README.md
)
