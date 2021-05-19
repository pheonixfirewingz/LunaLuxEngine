cmake_minimum_required(VERSION 3.17)
project(LunaLuxEngine C CXX)
set(CMAKE_CXX_STANDARD 20)
#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)

#main engine
add_library(LunaLuxEngine )

link_directories(${PROJECT_SOURCE_DIR}/Libs)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(LunaLuxEngine)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngine CrossWindow ${X11_LIBRARIES})
endif ()

add_executable(TestGame src/Game_src/Game.cpp)

target_link_libraries(TestGame LunaLuxEngine)