cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC IMPORTED)

#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow_src/BuildCrosswindowLib.cmake)
#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/GAA_src/GAALib.cmake)
#main engine
add_library(LunaLuxEngineCore src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/common/EnginePanic.h src/Core_src/common/EnginePanic.cpp src/Core_src/render/Common/ICamera.h )

target_link_libraries(LunaLuxEngineCore GAALib CrossWindow)

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)


target_link_libraries(TestGame LunaLuxEngineCore)

