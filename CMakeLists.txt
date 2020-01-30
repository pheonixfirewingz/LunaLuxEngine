cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATE,"Windows mode")
	if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
		message(ERROR,"must use Visual Studios Compiler to compile on Windows")
	endif()
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
message(STATE,"Linux mode")
find_package(GLEW REQUIRED)
find_package(X11 REQUIRED)
link_directories(${X11_LIBRARIES})
else()
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
add_subdirectory( ${PROJECT_SOURCE_DIR}/GLFW)
endif()

include_directories(${PROJECT_SOURCE_DIR}/CrossEngineIncludes STATIC IMPORTED)
include_directories(${PROJECT_SOURCE_DIR}/Physics_src STATIC)

add_library(LunaLuxEnginePhysicsLib Physics_src/LunaLuxEnginePhysics.h Physics_src/LunaLuxEnginePhysics.cpp)
add_library(LunaLuxEngineCoreLib Core_src/LunaLuxEngineCore.cpp Core_src/LunaLuxEngineCore.h Core_src/utils/IGame.h Core_src/render/IRender.h Core_src/window/Window.h Core_src/window/Window.cpp CrossEngineIncludes/LunaLuxEngine/types.h Core_src/render/OpenGL.cpp CrossEngineIncludes/LunaLuxEngine/Common_Header.h Core_src/render/DirectX.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	target_link_libraries(LunaLuxEngineCoreLib LunaLuxEnginePhysicsLib)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(LunaLuxEngineCoreLib LunaLuxEnginePhysicsLib GLEW::GLEW ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
endif()
include_directories(${PROJECT_SOURCE_DIR}/Core_src STATIC)

add_executable(TestGame test.cpp Game.cpp Game.h)

target_link_libraries(TestGame LunaLuxEngineCoreLib)
