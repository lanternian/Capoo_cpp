aux_source_directory(src/spine/ SRC)
add_library(spine-cpp ${SRC})
target_include_directories(spine-cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)