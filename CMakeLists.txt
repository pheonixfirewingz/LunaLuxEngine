cmake_minimum_required(VERSION 3.15)
project(LunaLuxEngine)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	message(STATE,"Windows mode")

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

include_directories(${PROJECT_SOURCE_DIR}/include STATIC IMPORTED)

add_library(LunaLuxEngineLib src/LunaLuxEngine.cpp src/LunaLuxEngine.h src/utils/IGame.h src/render/IRender.h src/window/Window.h src/window/Window.cpp src/utils/types.h src/render/OpenGL.cpp src/Common_Header.h src/common/Entity.cpp src/common/Entity.h src/render/DirectX.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	target_link_libraries(LunaLuxEngineLib ${OPENGL_LIBRARIES})
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(LunaLuxEngineLib GLEW::GLEW ${X11_LIBRARIES} ${OPENGL_LIBRARIES})
endif()


add_executable(LunaLuxEngine test.cpp Game.cpp Game.h)

target_link_libraries(LunaLuxEngine LunaLuxEngineLib)
