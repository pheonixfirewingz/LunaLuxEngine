#pragma once
#ifndef LIB_APP
#ifndef STATIC_LIB
#define LLVL_EXPORT __declspec(dllexport)
#else
#define LLVL_EXPORT
#endif
#else
#ifndef STATIC_LIB
#define LLVL_EXPORT __declspec(dllimport)
#else
#define LLVL_EXPORT
#endif
#endif
#include <tuple>
#include <vulkan/vulkan_core.h>
#include <vector>
//
// Created by luket on 28/04/2021.
// Copyright luket (c) 2021 All rights reserved.
namespace LunaLux
{
    //common functions
    LLVL_EXPORT void vulkanInit(void* native_handle,const std::tuple<int,int>& size,bool debug);
    LLVL_EXPORT void vulkanResizeSwapChain(const std::tuple<int,int>& size);
    LLVL_EXPORT void vulkanRe_establishSurface(void* native_handle);
    LLVL_EXPORT void vulkanCleanUp();

    //functions to access the surface data
    LLVL_EXPORT VkQueue vulkanGetGraphicsQueue();
    LLVL_EXPORT VkQueue vulkanGetPresentQueue();
    [[maybe_unused]] LLVL_EXPORT uint32_t vulkanGetPresentFamilyIndex();
    LLVL_EXPORT VkSurfaceFormatKHR vulkanGetSurfaceFormat();

    //functions to access the swapChain data
    LLVL_EXPORT VkSwapchainKHR vulkanGetSwapChain();
    LLVL_EXPORT uint32_t vulkanGetSwapChainImageCount();
    LLVL_EXPORT std::vector<VkImageView> vulkanGetSwapChainImageViews();
    LLVL_EXPORT std::vector<VkImage> vulkanGetSwapChainImages();

    //functions to access the Device data
    LLVL_EXPORT VkDevice vulkanGetDevice();
    LLVL_EXPORT unsigned int vulkanFindGpuMemoryType(unsigned int typeFilter, VkMemoryPropertyFlags flags);
    LLVL_EXPORT VkFormatProperties vulkanGetDeviceFormatProperties();
    LLVL_EXPORT uint32_t vulkanGetGraphicsFamilyIndex();
}
