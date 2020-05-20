cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC IMPORTED)
include_directories(${PROJECT_SOURCE_DIR}/src/Core_src STATIC)
include_directories(${PROJECT_SOURCE_DIR}/src/Game_src STATIC)

find_package(OpenGL REQUIRED)
link_directories(${OPENGL_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(GLEW REQUIRED)
    link_directories(${GLEW_LIBRARIES})
else()
    add_library(Glad src/Glad/glad.c Includes/glad/glad.h )
endif ()

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64")
endif()

#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow_src/BuildCrosswindowLib.cmake)
#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics_Api_Abstraction_src/GAALib.cmake)
#main engine
add_library(LunaLuxEngineCore src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/common/EnginePanic.h src/Core_src/common/EnginePanic.cpp src/Core_src/render/Common/ICamera.h )

target_link_libraries(LunaLuxEngineCore GAALib CrossWindow)

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)


target_link_libraries(TestGame LunaLuxEngineCore)

