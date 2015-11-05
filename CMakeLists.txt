cmake_minimum_required (VERSION 3.0)
project(ExomoSnake)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2.1 COMPONENTS graphics window system REQUIRED)

SET(CMAKE_CXX_FLAGS "-std=c++11")

add_subdirectory(src)

include_directories(${SFML_INCLUDE_DIR})
add_executable(snake Main.cpp)
target_link_libraries(snake exomo_snake_lib)

install(TARGETS snake DESTINATION .)
install(DIRECTORY resources DESTINATION .)
