#include "API/VulkanLib.h"
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include "Componants/Device.hpp"
#include "Componants/Surface.hpp"
#include "Componants/SwapChain.hpp"
#include <memory>

namespace LunaLux
{
//this is the Vulkan device Handler
std::unique_ptr<Device> device;
//this is the Vulkan surface Handler
std::unique_ptr<Surface> surface;
//this is the Vulkan SwapChain Handler
std::unique_ptr<SwapChain> swapChain;

//this is so we can initialize the vulkan entity handler objects to be used
void vulkanInit(void *native_handle, const std::tuple<int, int> &size)
{
    const auto &[width, height] = size;
    device = std::make_unique<Device>();
    surface = std::make_unique<Surface>(device.get(), native_handle);
    swapChain = std::make_unique<SwapChain>(surface.get(), device.get(), width, height);
}

//this is a wrapper for the reset function of the SwapChain handler
void vulkanResizeSwapChain(const std::tuple<int, int> &size)
{
    const auto &[width, height] = size;
    swapChain->reset(width, height);
}

//this is so that the global Internal vulkan entity handlers can be cleaned up and deleted
void vulkanCleanUp() noexcept
{
    swapChain = nullptr;
    surface = nullptr;
    device = nullptr;
}

//this is a wrapper for the reset function of the surface handler
void vulkanRe_establishSurface(void *native_handle)
{
    surface->reset(native_handle);
}

//this is a wrapper get the Vulkan Graphics Queue from the surface handler
VkQueue vulkanGetGraphicsQueue() noexcept
{
    return surface->getGraphicsQueue();
}

//this is a wrapper get the Vulkan Present Queue from the surface handler
VkQueue vulkanGetPresentQueue() noexcept
{
    return surface->getPresentQueue();
}

//this is a wrapper get the Vulkan Graphics Family Index from the device handler
uint32_t vulkanGetGraphicsFamilyIndex() noexcept
{
    return device->getFamilyIndex();
}

//this is a wrapper get the Vulkan Present Family Index from the surface handler
uint32_t vulkanGetPresentFamilyIndex() noexcept
{
    return surface->getPresentFamilyIndex();
}

//this is a wrapper get the Vulkan Surface Format from the surface handler
VkSurfaceFormatKHR vulkanGetSurfaceFormat() noexcept
{
    return surface->getSurfaceFormat();
}

//this is a wrapper get the Vulkan SwapChain from the swap chain handler
VkSwapchainKHR vulkanGetSwapChain()
{
    return swapChain->getSwapChain();
}

//this is a wrapper get the Vulkan SwapChain image count from the swap chain handler
uint32_t vulkanGetSwapChainImageCount() noexcept
{
    return swapChain->getImageCount();
}

//this is a wrapper get the Vulkan SwapChain ImageViews as a vector from the swap chain handler
std::vector<VkImageView> vulkanGetSwapChainImageViews() noexcept
{
    return swapChain->getSwapChainImageViews();
}

//this is a wrapper get the Vulkan SwapChain Images as a vector from the swap chain handler
std::vector<VkImage> vulkanGetSwapChainImages() noexcept
{
    return swapChain->getSwapChainImages();
}

//this is a wrapper get the Vulkan SwapChain Image View as a vector from the surface handler
VkDevice vulkanGetDevice()
{
    return device->getDev();
}

//this is a wrapper to ask the device handler to find the right gpu memory type and return it to the library user
unsigned int vulkanFindGpuMemoryType(unsigned int typeFilter, VkMemoryPropertyFlags flags)
{
    return device->findGpuMemoryType(typeFilter, flags);
}

//this is a wrapper get the Vulkan Device Format Properties from the device handler
VkFormatProperties vulkanGetDeviceFormatProperties() noexcept
{
    return device->getFormProperties();
}
} // namespace LunaLux
