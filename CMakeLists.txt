cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATE,"Windows mode")
	find_library(DX libd2d1.lib
			HINTS ${PROJECT_SOURCE_DIR}/lib)
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

include_directories(${PROJECT_SOURCE_DIR}/CrossEngineIncludes STATIC)
include_directories(${PROJECT_SOURCE_DIR}/include STATIC IMPORTED)
include_directories(${PROJECT_SOURCE_DIR}/Physics_src STATIC)

add_library(LunaLuxEnginePhysicsLib Physics_src/LunaLuxEnginePhysics.h Physics_src/LunaLuxEnginePhysics.cpp)
add_library(LunaLuxEngineCoreLib Core_src/LunaLuxEngineCore.cpp Core_src/LunaLuxEngineCore.h Core_src/utils/IGame.h Core_src/render/IRender.h Core_src/window/Window.h Core_src/window/Window.cpp CrossEngineIncludes/types.h Core_src/render/OpenGL.cpp CrossEngineIncludes/Common_Header.h Core_src/common/Entity.cpp Core_src/common/Entity.h Core_src/render/DirectX.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
<<<<<<< Updated upstream
	target_link_libraries(LunaLuxEngineCoreLib LunaLuxEnginePhysicsLib)
=======
	target_link_libraries(LunaLuxEngineLib ${DX})
>>>>>>> Stashed changes
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(LunaLuxEngineCoreLib LunaLuxEnginePhysicsLib GLEW::GLEW ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
endif()
include_directories(${PROJECT_SOURCE_DIR}/Core_src STATIC)

add_executable(TestGame test.cpp Game.cpp Game.h)

target_link_libraries(TestGame LunaLuxEngineCoreLib)
