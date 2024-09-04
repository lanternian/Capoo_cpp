add_library(jsoncpp jsoncpp.cpp)
target_include_directories(jsoncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_definitions(jsoncpp PRIVATE JSON_DLL_BUILD)
