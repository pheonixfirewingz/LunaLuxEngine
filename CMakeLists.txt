cmake_minimum_required(VERSION 3.17)
project(LunaLuxEngine)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS TRUE)
#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)
include_directories(${PROJECT_SOURCE_DIR}/src STATIC)
find_package(Vulkan REQUIRED FATAL_ERROR)
if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    FIND_PACKAGE( X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
endif()
include_directories(${Vulkan_INCLUDE_DIRS})
configure_file(src/Debug.h.in ../src/Debug.h @ONLY)
add_subdirectory(Libs)
#main engine
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined,implicit-integer-truncation,implicit-integer-arithmetic-value-change,implicit-conversion,integer,nullability")

add_executable(LunaLuxEngine    src/Test.cpp
                                src/EngineError.cpp
                                src/LunaLuxEngine.cpp
                                src/Renderer/Vulkan/VulkanRenderer.cpp
                                src/Renderer/RenderManager.cpp
                                src/Renderer/DirectX12/DirctX12Renderer.cpp
                                src/Network/NetworkManager.cpp
                                src/utils/StringUtils.cpp src/EntitySystem/Component.h src/utils/BinaryTree.hpp src/EntitySystem/Entity.h)

target_link_libraries(LunaLuxEngine LunaLuxWindowLib LunaLuxNetLib LunaLuxVulkanLib LunaLuxVulkanUtilLib)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngine ${X11_xcb_LIB} ${X11_LIBRARIES})
endif ()
if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(LunaLuxEngine LunaLuxDirectX12Lib)
endif ()