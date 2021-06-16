#include "Validator.h"
#include <stdexcept>
//
// Created by luket on 21/05/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
namespace LunaLux
{
#if ENABLE_VULKAN_FUNCTION_ERROR_CHECK == 1
//this is used to make the code look cleaner
#define case_(x)    \
    case x:         \
    {               \
        return #x;  \
    }

//we put the vulkan result in and get is back as a string
std::string getError(VkResult result)
{
    switch (result)
    {
    case_(VK_NOT_READY)
    case_(VK_TIMEOUT)
    case_(VK_EVENT_SET)
    case_(VK_EVENT_RESET)
    case_(VK_INCOMPLETE)
    case_(VK_ERROR_OUT_OF_HOST_MEMORY)
    case_(VK_ERROR_OUT_OF_DEVICE_MEMORY)
    case_(VK_ERROR_INITIALIZATION_FAILED)
    case_(VK_ERROR_DEVICE_LOST)
    case_(VK_ERROR_MEMORY_MAP_FAILED)
    case_(VK_ERROR_LAYER_NOT_PRESENT)
    case_(VK_ERROR_EXTENSION_NOT_PRESENT)
    case_(VK_ERROR_FEATURE_NOT_PRESENT)
    case_(VK_ERROR_INCOMPATIBLE_DRIVER)
    case_(VK_ERROR_TOO_MANY_OBJECTS)
    case_(VK_ERROR_FORMAT_NOT_SUPPORTED)
    case_(VK_ERROR_FRAGMENTED_POOL)
    case_(VK_ERROR_UNKNOWN)
    case_(VK_ERROR_OUT_OF_POOL_MEMORY)
    case_(VK_ERROR_INVALID_EXTERNAL_HANDLE)
    case_(VK_ERROR_FRAGMENTATION)
    case_(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS)
    case_(VK_ERROR_SURFACE_LOST_KHR)
    case_(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
    case_(VK_SUBOPTIMAL_KHR)
    case_(VK_ERROR_OUT_OF_DATE_KHR)
    case_(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
    case_(VK_ERROR_VALIDATION_FAILED_EXT)
    case_(VK_ERROR_INVALID_SHADER_NV)
    case_(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
    case_(VK_ERROR_NOT_PERMITTED_EXT)
    case_(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)
    case_(VK_THREAD_IDLE_KHR)
    case_(VK_THREAD_DONE_KHR)
    case_(VK_OPERATION_DEFERRED_KHR)
    case_(VK_OPERATION_NOT_DEFERRED_KHR)
    case_(VK_PIPELINE_COMPILE_REQUIRED_EXT)
    default:
        throw std::runtime_error("LunaLuxVulkanLib - VULKAN_RUNTIME_FAILURE: vulkan returned a non standard result!");
    }
}

//if vulkan returns VK_SUCCESS then this function is a no op else we alert the lib user that vulkan returned an error
void Validate(VkResult result,const char* fun_name)
{
    if(result == VK_SUCCESS)
    {
        return;
    }
    printf("LunaLuxVulkanLib: %s return %s\n",fun_name, getError(result).c_str());
}
#endif
}