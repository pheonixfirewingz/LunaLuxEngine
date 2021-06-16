cmake_minimum_required(VERSION 3.18)
include(meta/debug_macros.cmake)

configure_file(src/Debug.h.in ../src/Debug.h @ONLY)

add_library(LunaLuxVulkanUtilLib SHARED src/Catagory/Other.cpp
                                        src/Catagory/Destroyers.cpp
                                        src/Catagory/StructCreation.cpp
                                        src/Catagory/Creators.cpp)

target_link_libraries(LunaLuxVulkanUtilLib LunaLuxVulkanLib ${Vulkan_LIBRARIES})