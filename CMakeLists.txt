cmake_minimum_required(VERSION 3.10)


# 项目名称和版本
project(DesktopPet)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置SFML的根目录和导入库路径
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML-2.6.1")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")



# 添加项目的源文件
add_subdirectory(spine-cpp)
add_subdirectory(spine-sfml-cpp)

add_executable(DesktopPet src/loadCapoo.cpp)

target_link_libraries(DesktopPet spine-cpp spine-sfml-cpp)

# 添加包含目录
target_include_directories(DesktopPet PUBLIC ${SFML_INCLUDE_DIR})

# 链接库到目标文件
target_link_libraries(DesktopPet $<$<CONFIG:Debug>:${SFML_LIBRARY_DIR}/sfml-main-d.lib> $<$<CONFIG:Release>:${SFML_LIBRARY_DIR}/sfml-main.lib>)
target_link_libraries(DesktopPet $<$<CONFIG:Debug>:${SFML_LIBRARY_DIR}/sfml-graphics-s-d.lib> $<$<CONFIG:Release>:${SFML_LIBRARY_DIR}/sfml-graphics-s.lib>)
target_link_libraries(DesktopPet $<$<CONFIG:Debug>:${SFML_LIBRARY_DIR}/sfml-window-s-d.lib> $<$<CONFIG:Release>:${SFML_LIBRARY_DIR}/sfml-window-s.lib>)
target_link_libraries(DesktopPet $<$<CONFIG:Debug>:${SFML_LIBRARY_DIR}/sfml-system-s-d.lib> $<$<CONFIG:Release>:${SFML_LIBRARY_DIR}/sfml-system-s.lib>)

target_link_libraries(DesktopPet ${SFML_LIBRARY_DIR}/freetype.lib)
target_link_libraries(DesktopPet opengl32)
target_link_libraries(DesktopPet gdi32)
target_link_libraries(DesktopPet winmm)

add_definitions(-DSFML_STATIC)

# copy data to build directory
add_custom_command(TARGET DesktopPet
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_LIST_DIR}/data $<TARGET_FILE_DIR:DesktopPet>/data)

# add_custom_command(TARGET DesktopPet POST_BUILD COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug/DesktopPet.exe)
