#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#if __has_include(<windows.h>)
#ifndef LIB_APP
#    define LLVL_EXPORT __declspec(dllexport)
#else
#    define LLVL_EXPORT __declspec(dllimport)
#endif
#else
#ifndef LIB_APP
#ifndef STATIC_LIB
#define LLVL_EXPORT __attribute__((visibility("default")))
#else
#define LLVL_EXPORT
#endif
#endif
#endif
#include <tuple>
#include <vector>
#include <vulkan/vulkan_core.h>
//TODO: write documentation
namespace LunaLux
{
// common functions
LLVL_EXPORT void vulkanInit(void *native_handle, const std::tuple<int, int> &size);
LLVL_EXPORT void vulkanResizeSwapChain(const std::tuple<int, int> &size);
LLVL_EXPORT void vulkanRe_establishSurface(void *native_handle);
LLVL_EXPORT void vulkanCleanUp() noexcept;

// functions to access the surface data
LLVL_EXPORT VkQueue vulkanGetGraphicsQueue() noexcept;
LLVL_EXPORT VkQueue vulkanGetPresentQueue() noexcept;
[[maybe_unused]] LLVL_EXPORT uint32_t vulkanGetPresentFamilyIndex() noexcept;
LLVL_EXPORT VkSurfaceFormatKHR vulkanGetSurfaceFormat() noexcept;

// functions to access the swapChain data
LLVL_EXPORT VkSwapchainKHR vulkanGetSwapChain();
LLVL_EXPORT uint32_t vulkanGetSwapChainImageCount() noexcept;
LLVL_EXPORT std::vector<VkImageView> vulkanGetSwapChainImageViews() noexcept;
LLVL_EXPORT std::vector<VkImage> vulkanGetSwapChainImages() noexcept;

// functions to access the Device data
LLVL_EXPORT ::VkDevice vulkanGetDevice();
LLVL_EXPORT unsigned int vulkanFindGpuMemoryType(unsigned int typeFilter, VkMemoryPropertyFlags flags);
LLVL_EXPORT VkFormatProperties vulkanGetDeviceFormatProperties() noexcept;
LLVL_EXPORT uint32_t vulkanGetGraphicsFamilyIndex() noexcept;
} // namespace LunaLux
