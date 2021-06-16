#pragma once
//
// Created by luket on 21/05/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "../Debug.h"
#include <vulkan/vulkan_core.h>
#include <string>
namespace LunaLux
{
//if cmake ENABLE_VULKAN_FUNCTION_ERROR_CHECK enabled then use validator function
#if ENABLE_VULKAN_FUNCTION_ERROR_CHECK == 1
//this is used to handle vulkan result
void Validate(VkResult,const char *);
#define TEST(x,y) Validate(x y,#x)
#else
#define TEST(x,y) x y
#endif
} // namespace LunaLux
