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
    find_package(X11 REQUIRED)
    find_package(GLEW REQUIRED)
    link_directories(${GLEW_LIBRARIES})
    link_directories(${X11_LIBRARIES})
else()
    add_library(Glad src/Glad/glad.c Includes/glad/glad.h)
endif ()

add_library(LunaLuxEngineCore src/Core_src/LunaLuxEngineCore.cpp src/Core_src/LunaLuxEngineCore.h src/Core_src/render/Renderer.h src/Core_src/render/Renderer.cpp src/Core_src/fs/Reader.h src/Core_src/render/Common/IRender.h src/Core_src/render/OpenGL/OpenGLRenderer.h src/Core_src/render/OpenGL/OpenGLRenderer.cpp src/Core_src/window/IWindow.h src/Core_src/window/Window.h src/Core_src/window/Window.cpp src/Core_src/window/Win32Window.h src/Core_src/window/Win32Window.cpp src/Core_src/render/Buffer.h src/Core_src/render/Buffer.cpp src/Core_src/render/Shader.h src/Core_src/render/Shader.cpp src/Core_src/render/Common/IBuffer.h src/Core_src/render/Common/IRender.h src/Core_src/render/Common/IContext.h src/Core_src/render/Common/IShader.h src/Core_src/render/OpenGL/OpenGLBuffer.h src/Core_src/render/OpenGL/OpenGLBuffer.cpp src/Core_src/render/OpenGL/OpenGLContext.h src/Core_src/render/OpenGL/OpenGLContext.cpp src/Core_src/render/OpenGL/OpenGLShader.h src/Core_src/render/OpenGL/OpenGLShader.cpp src/Core_src/common/EnginePanic.h src/Core_src/common/EnginePanic.cpp src/Core_src/common/Event.h src/Core_src/render/Common/ICamera.h src/Core_src/render/Common/IShaderLayout.h src/Core_src/window/X11Window.cpp src/Core_src/window/X11Window.h)

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)

target_link_libraries(LunaLuxEngineCore ${OPENGL_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngineCore ${GLEW_LIBRARIES} ${X11_LIBRARIES})
else()
    target_link_libraries(LunaLuxEngineCore Glad)
endif ()

target_link_libraries(TestGame LunaLuxEngineCore)

