cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        message(ERROR,"must use Visual Studios Compiler to compile on Windows")
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC IMPORTED)
include_directories(${PROJECT_SOURCE_DIR}/Physics_src STATIC)
include_directories(${PROJECT_SOURCE_DIR}/Core_src STATIC)
include(${PROJECT_SOURCE_DIR}/CMakeScripts/CoreLib.cmake)

add_executable(TestGame Game_src/test.cpp Game_src/Game.cpp Game_src/Game.h)
target_link_libraries(TestGame LunaLuxEngineCoreLib)