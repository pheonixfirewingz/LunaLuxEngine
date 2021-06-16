cmake_minimum_required(VERSION 3.18)
include(meta/debug_macros.cmake)

configure_file(src/Debug.h.in ../src/Debug.h @ONLY)

add_library(LunaLuxVulkanLib SHARED src/VulkanLib.cpp
                                    src/Componants/Device.cpp
                                    src/Componants/Validator.cpp)

target_link_libraries(LunaLuxVulkanLib LunaLuxWindowLib ${Vulkan_LIBRARIES})