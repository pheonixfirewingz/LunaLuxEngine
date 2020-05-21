cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)
include_directories(${PROJECT_SOURCE_DIR}/../LunaLuxEngine_GAA_Lib/Includes STATIC)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(OpenGL REQUIRED)
    find_package(VULKAN REQUIRED)
    find_package(GLEW REQUIRED)
    link_directories(${GLEW_LIBRARIES} ${VULKAN_LIBRARIES} ${OPENGL_LIBRARIES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    find_package(OpenGL REQUIRED)
    link_directories(${OPENGL_LIBRARIES})
    include_directories("C:/VulkanSDK/1.2.131.2/Include/vulkan")
    link_directories("C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64")
    link_directories("C:/VulkanSDK/1.2.131.2/Lib")
else()
    #this dose not support mac yet
endif ()

#cross window libbary
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow_src/BuildCrosswindowLib.cmake)
#main engine
add_library(LunaLuxEngineCore src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/common/EnginePanic.h src/Core_src/common/EnginePanic.cpp src/Core_src/render/Common/ICamera.h )
link_directories(${PROJECT_SOURCE_DIR}/../LunaLuxEngine_GAA_Lib/cmake-build-debug)
link_directories(${PROJECT_SOURCE_DIR}/Libs)

target_link_libraries(LunaLuxEngineCore LunaLuxEngine_GAA_Lib CrossWindow)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngineCore ${GLEW_LIBRARIES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(LunaLuxEngineCore Glad d3d11 d3dx11 dxguid)
else()
    target_link_libraries(LunaLuxEngineCore Glad)
endif ()

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)


target_link_libraries(TestGame LunaLuxEngineCore)

