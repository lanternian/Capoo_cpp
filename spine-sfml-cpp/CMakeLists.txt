if(MSVC)
	message("MSCV detected")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_CRT_SECURE_NO_WARNINGS")
else()
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -std=c99")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wnon-virtual-dtor -pedantic -std=c++11 -fno-exceptions -fno-rtti")
endif()

# Define spine-sfml-cpp library
include_directories(${SFML_INCLUDE_DIR})
file(GLOB INCLUDES "src/**/*.h")
file(GLOB SOURCES "src/**/*.cpp")
add_library(spine-sfml-cpp STATIC ${SOURCES} ${INCLUDES})
target_include_directories(spine-sfml-cpp PUBLIC src)
target_link_libraries(spine-sfml-cpp LINK_PUBLIC spine-cpp)

