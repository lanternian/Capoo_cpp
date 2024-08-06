cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME CapooPals)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB THIRD_PARTY_SOURCES "3party/**/*.cpp")
file(GLOB MY_SOURCES "src/*.cpp")
set(SRC ${THIRD_PARTY_SOURCES} ${MY_SOURCES})
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-main sfml-window)

# copy data to build directory
add_custom_command(TARGET ${PROJECT_NAME}
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_LIST_DIR}/data $<TARGET_FILE_DIR:${PROJECT_NAME}>/data)

