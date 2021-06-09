cmake_minimum_required(VERSION 3.17)
project(LunaLuxEngine CXX)
set(CMAKE_CXX_STANDARD 20)
#includes for the projects
include_directories(${PROJECT_SOURCE_DIR}/Includes STATIC)
include_directories(${PROJECT_SOURCE_DIR}/src STATIC)
include_directories(C:\\VulkanSDK\\1.2.176.1\\Include STATIC)

#main engine
add_executable(LunaLuxEngine    src/Test.cpp
                                src/EngineError.cpp
                                src/LunaLuxEngine.cpp
                                src/Renderer/Vulkan/VulkanRenderer.cpp
                                src/Renderer/RenderManager.cpp
                                src/utils/StringUtils.cpp)

target_link_libraries(LunaLuxEngine ${PROJECT_SOURCE_DIR}/Libs/LunaLuxWindowLib.lib
                                    ${PROJECT_SOURCE_DIR}/Libs/LunaLuxVulkanLib.lib
                                    ${PROJECT_SOURCE_DIR}/Libs/LunaLuxVulkanUtilLib.lib)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LunaLuxEngine ${X11_LIBRARIES})
endif ()