cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine C CXX)
set(CMAKE_CXX_STANDARD 20)
#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(X11 REQUIRED)
    find_library( DL_LIBRARY libdl.so)
endif ()
find_package(OpenGL REQUIRED)
include(${CMAKE_CURRENT_SOURCE_DIR}/src/CrossWindow_src/BuildCrosswindowLib.cmake)
#main engine
add_library(LunaLuxEngineCore
        src/Core_src/render/Common/stb_image.h
        src/Core_src/LunaLuxEngineCore.cpp
        src/Core_src/LunaLuxEngineCore.h
        src/Core_src/render/Renderer.h
        src/Core_src/render/Renderer.cpp
        src/Core_src/render/Common/IRender.h
        src/Core_src/render/OpenGL/OpenGLRenderer.h
        src/Core_src/render/OpenGL/OpenGLRenderer.cpp
        src/Core_src/render/OpenGL/glad.c
        src/Core_src/render/Buffer.h
        src/Core_src/render/Buffer.cpp
        src/Core_src/render/Shader.h
        src/Core_src/render/Shader.cpp
        src/Core_src/render/Common/IBuffer.h
        src/Core_src/render/Common/IRender.h
        src/Core_src/render/Common/IShader.h
        src/Core_src/render/OpenGL/OpenGLBuffer.h
        src/Core_src/render/OpenGL/OpenGLBuffer.cpp
        src/Core_src/render/OpenGL/OpenGLShader.h
        src/Core_src/render/OpenGL/OpenGLShader.cpp
        src/Core_src/render/OpenGL/OpenGLTexture.h
        src/Core_src/render/OpenGL/OpenGLTexture.cpp
        src/Core_src/common/EnginePanic.h
        src/Core_src/common/EnginePanic.cpp
        src/Core_src/render/Common/stb_image.cpp
        src/Core_src/render/OpenGL/OpenGLUtils.cpp
        src/Core_src/render/OpenGL/OpenGLUtils.h
        src/Core_src/fs/FileManager.cpp
        src/Core_src/fs/FileManager.h
        src/Core_src/fs/common/IFileManager.h
        src/Core_src/fs/common/SeconderyTokenizer.cpp
        src/Core_src/fs/common/PrimaryTokenizer.cpp
        src/Core_src/fs/common/ShaderParce.cpp
        src/Core_src/fs/common/GLSLConverter.cpp
        src/Core_src/fs/common/ShaderParce.h
        src/Core_src/fs/Windows/WindowsFileManager.cpp
        src/Core_src/fs/Windows/WindowsFileManager.h src/Core_src/math/LLE_Vector.h src/Core_src/math/LLE_Vector.cpp src/Core_src/math/LLE_VectorMath.cpp src/Core_src/math/LLE_VectorMath.h src/Core_src/math/LLE_Matrix.cpp src/Core_src/math/LLE_Matrix.h src/Core_src/math/LLE_MatrixMath.cpp src/Core_src/math/LLE_MatrixMath.h src/Core_src/render/Common/IShaderLayout.h src/Core_src/render/ShaderLayout.cpp src/Core_src/render/ShaderLayout.h src/Core_src/render/OpenGL/OpenGLShaderLayout.cpp src/Core_src/render/OpenGL/OpenGLShaderLayout.h src/Core_src/render/Common/ITexture.h src/Core_src/render/Texture.cpp src/Core_src/render/Texture.h)
link_directories(${PROJECT_SOURCE_DIR}/Libs)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(LunaLuxEngineCore CrossWindow opengl32 Winmm)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngineCore CrossWindow ${X11_LIBRARIES} ${OPENGL_LIBRARIES} ${DL_LIBRARY})
endif ()

add_executable(TestGame src/Game_src/Game.cpp src/Game_src/main.cpp)

target_link_libraries(TestGame LunaLuxEngineCore)