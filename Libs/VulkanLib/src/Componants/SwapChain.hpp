#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include "Surface.hpp"

// TODO: this documentation is lacking and will need expanding in the future
namespace LunaLux
{
// this is used as a handler for the vulkan swap chain
class SwapChain
{
    // this is a pointer of the wrap for the device
    Device *device = nullptr;
    // this is a pointer of the wrap for the Surface
    Surface *surface = nullptr;
    // this is a memory pointer to the swapChain
    VkSwapchainKHR swap_chain = nullptr;
    // this is a memory pointer to the swap chain present mode
    VkPresentModeKHR present_mode = VK_PRESENT_MODE_FIFO_KHR;
    // this is used to store image count of the swap chain
    uint32_t ImageCount = 0;
    // this is a vector used to store the swap chain image
    std::vector<VkImage> swapChain_images{};
    // this is a vector used to store the swap chain image views
    std::vector<VkImageView> swapChain_image_views{};

    void create(uint32_t width, uint32_t height, bool firstCall)
    {
        // this is a pointer to the the bits that tell use what the surface supports
        VkSurfaceTransformFlagsKHR preTransform;
        if (surface->getSurfaceCapabilities().supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
        {
            preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        }
        else
        {
            // so the surface dose not support VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR so we set preTransform to what we
            // do support so we don't crash
            preTransform = surface->getSurfaceCapabilities().currentTransform;
        }

        // Find a supported composite alpha mode - one of these is guaranteed to be set
        VkCompositeAlphaFlagBitsKHR compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[4] = {
            VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
            VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
            VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
        };
        for (auto &compositeAlphaFlag : compositeAlphaFlags)
        {
            if (surface->getSurfaceCapabilities().supportedCompositeAlpha & compositeAlphaFlag)
            {
                compositeAlpha = compositeAlphaFlag;
                break;
            }
        }

        // now we are creating the information struct to pass it to the vulkan driver to created use a pointer to a swap
        // chain on the driver side
        VkSwapchainCreateInfoKHR swapChain_create_info{};
        swapChain_create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapChain_create_info.surface = surface->getSurface();
        swapChain_create_info.minImageCount = surface->getSurfaceCapabilities().minImageCount;
        swapChain_create_info.imageFormat = surface->getSurfaceFormat().format;
        swapChain_create_info.imageColorSpace = surface->getSurfaceFormat().colorSpace;
        // if this is the first time creating a swap chain it is against the vulkan spec to use the window size
        //  so we need to use the Surface max size
        if (!firstCall)
        {
            swapChain_create_info.imageExtent = {width, height};
        }
        else
        {
            swapChain_create_info.imageExtent = surface->getSurfaceCapabilities().maxImageExtent;
        }

        swapChain_create_info.imageArrayLayers = 1;
        swapChain_create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapChain_create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapChain_create_info.queueFamilyIndexCount = 0;
        swapChain_create_info.pQueueFamilyIndices = nullptr;
        swapChain_create_info.preTransform = static_cast<VkSurfaceTransformFlagBitsKHR>(preTransform);
        swapChain_create_info.compositeAlpha = compositeAlpha;
        swapChain_create_info.presentMode = present_mode;
        swapChain_create_info.clipped = VK_TRUE;
        // if this is not first call we need to tell the driver the old swapchain so if we have something in present
        // flying we don't crash the vulkan driver
        //  because this will result in a device crash and will cause the lib user program to crash
        if (!firstCall)
        {
            // we store the pointer to the old swap chain in a temp variable
            VkSwapchainKHR oldSwapChain = swap_chain;
            // we delete the old swap chain from the constant variable memory ready for new vulkan swap chain
            swap_chain = nullptr;
            swapChain_create_info.oldSwapchain = oldSwapChain;
            // we ask vulkan for the swap chain
            TEST(vkCreateSwapchainKHR, (device->getDev(), &swapChain_create_info, nullptr, &swap_chain));
            for (auto view : swapChain_image_views)
            {
                vkDestroyImageView(device->getDev(), view, nullptr);
            }
            // we ask vulkan to destroy the old swap chain
            vkDestroySwapchainKHR(device->getDev(), oldSwapChain, nullptr);
        }
        else
        {
            swapChain_create_info.oldSwapchain = nullptr;
            // we ask vulkan for the swap chain
            TEST(vkCreateSwapchainKHR, (device->getDev(), &swapChain_create_info, nullptr, &swap_chain));
        }

        //TODO: finish documentation
        TEST(vkGetSwapchainImagesKHR, (device->getDev(), swap_chain, &ImageCount, nullptr));
        swapChain_images.resize(ImageCount);
        swapChain_image_views.resize(ImageCount);
        TEST(vkGetSwapchainImagesKHR, (device->getDev(), swap_chain, &ImageCount, swapChain_images.data()));

        for (uint32_t i = 0; i < ImageCount; ++i)
        {
            VkImageViewCreateInfo image_view_create_info{};
            image_view_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
            image_view_create_info.image = swapChain_images[i];
            image_view_create_info.viewType = VK_IMAGE_VIEW_TYPE_2D;
            image_view_create_info.format = surface->getSurfaceFormat().format;
            image_view_create_info.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
            image_view_create_info.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
            image_view_create_info.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
            image_view_create_info.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
            image_view_create_info.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
            image_view_create_info.subresourceRange.baseMipLevel = 0;
            image_view_create_info.subresourceRange.levelCount = 1;
            image_view_create_info.subresourceRange.baseArrayLayer = 0;
            image_view_create_info.subresourceRange.layerCount = 1;

            TEST(vkCreateImageView, (device->getDev(), &image_view_create_info, nullptr, &swapChain_image_views[i]));
        }
    }

    void Destroy()
    {
        for (auto view : swapChain_image_views)
        {
            vkDestroyImageView(device->getDev(), view, nullptr);
        }
        vkDestroySwapchainKHR(device->getDev(), swap_chain, nullptr);
    }

  public:
    explicit SwapChain(Surface *surf, Device *dev, uint32_t width, uint32_t height)
        : surface(surf)
        , device(dev)
    {
        {
            uint32_t present_mode_count = 0;
            VkPresentModeKHR *present_mode_list;
            TEST(vkGetPhysicalDeviceSurfacePresentModesKHR,
                 (device->getPDev(), surface->getSurface(), &present_mode_count, nullptr));
            present_mode_list = new VkPresentModeKHR[present_mode_count];
            TEST(vkGetPhysicalDeviceSurfacePresentModesKHR,
                 (device->getPDev(), surface->getSurface(), &present_mode_count, present_mode_list));
            for (uint32_t i = 0; i <= present_mode_count; i++)
            {
                if (present_mode_list[i] == VK_PRESENT_MODE_MAILBOX_KHR)
                    present_mode = present_mode_list[i];
            }
        }
        create(width, height, true);
    }

    void reset(uint32_t width, uint32_t height)
    {
        create(width, height, false);
    }

    ~SwapChain()
    {
        Destroy();
    }
    [[nodiscard]] VkSwapchainKHR getSwapChain() const
    {
        return swap_chain;
    }

    [[nodiscard]] uint32_t getImageCount() const
    {
        return ImageCount;
    }

    [[nodiscard]] const std::vector<VkImageView> &getSwapChainImageViews() const
    {
        return swapChain_image_views;
    }

    [[nodiscard]] const std::vector<VkImage> &getSwapChainImages() const
    {
        return swapChain_images;
    }
};
}; // namespace LunaLux