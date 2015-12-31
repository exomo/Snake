cmake_minimum_required (VERSION 3.0)
project(ExomoSnake)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SFML 2.1 COMPONENTS audio graphics window system REQUIRED)

SET(CMAKE_CXX_FLAGS "-std=c++11")
if(WIN32 AND "${CMAKE_BUILD_TYPE}" STREQUAL "Release")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows")
endif()

add_subdirectory(src)

include_directories(${SFML_INCLUDE_DIR})
add_executable(snake Main.cpp)
target_link_libraries(snake exomo_snake_lib)

install(TARGETS snake DESTINATION .)
install(FILES snakeHighscore.esh DESTINATION .)
install(DIRECTORY resources DESTINATION .)

if(WIN32)
install(FILES ${SFML_INCLUDE_DIR}/../bin/openal32.dll
        DESTINATION .)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
install(FILES ${SFML_AUDIO_DLL_RELEASE}
			  ${SFML_GRAPHICS_DLL_RELEASE}
			  ${SFML_SYSTEM_DLL_RELEASE}
			  ${SFML_WINDOW_DLL_RELEASE}
        DESTINATION .)
else()
install(FILES ${SFML_AUDIO_DLL_DEBUG}
			  ${SFML_GRAPHICS_DLL_DEBUG}
			  ${SFML_SYSTEM_DLL_DEBUG}
			  ${SFML_WINDOW_DLL_DEBUG}
        DESTINATION .)
endif()
endif()
