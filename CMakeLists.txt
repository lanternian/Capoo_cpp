cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME CapooPals_Cpp)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(THIRDPARTY_DIRECTORY ${PROJECT_SOURCE_DIR}/3party)
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
set(SFML_STATIC_LIBRARIES FALSE)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_subdirectory(${THIRDPARTY_DIRECTORY}/jsoncpp-1.9.5)
add_subdirectory(${THIRDPARTY_DIRECTORY}/spine-sfml-4.1.x)

file(GLOB SRC "src/*.cpp")
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} sfml-graphics jsoncpp spine-sfml)

if(WIN32)
    target_sources(${PROJECT_NAME} PRIVATE data/resources.rc)
    target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
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

