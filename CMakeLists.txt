cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)
include_directories(${PROJECT_SOURCE_DIR}/../LunaLuxEngine_GAA_Lib/Includes STATIC)

#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow_src/BuildCrosswindowLib.cmake)
#main engine
add_library(LunaLuxEngineCore src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/common/EnginePanic.h src/Core_src/common/EnginePanic.cpp src/Core_src/render/Common/ICamera.h )
link_directories(${PROJECT_SOURCE_DIR}/libs)

target_link_libraries(LunaLuxEngineCore LunaLuxEngine_GAA_Lib CrossWindow)

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)


target_link_libraries(TestGame LunaLuxEngineCore)

