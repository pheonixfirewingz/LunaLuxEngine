cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC IMPORTED)
include_directories(${PROJECT_SOURCE_DIR}/src/Core_src STATIC)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
link_directories(${Vulkan_LIBRARY})
link_directories(${OPENGL_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories(C:/VulkanSDK/1.2.131.2/Include STATIC)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(X11 REQUIRED)
    link_directories(${X11_LIBRARIES})
endif()

add_library(LunaLuxEngineCoreLib src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/fs/Reader.h src/Core_src/render/Common/IRender.H src/Core_src/render/Common/GPUInstance.cpp src/Core_src/render/OpenGL/OpenGLRenderer.h src/Core_src/render/OpenGL/OpenGLRenderer.cpp src/Glad/glad.c src/Core_src/window/IWindow.h src/Core_src/window/Window.h src/Core_src/window/Window.cpp src/Core_src/window/Win32Window.h src/Core_src/window/Win32Window.cpp)

target_link_libraries(LunaLuxEngineCoreLib ${Vulkan_LIBRARY} ${OPENGL_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngineCoreLib ${X11_LIBRARIES})
endif()

add_executable(TestGame src/Game_src/test.cpp src/Game_src/Game.cpp src/Game_src/Game.h)
target_link_libraries(TestGame LunaLuxEngineCoreLib)
