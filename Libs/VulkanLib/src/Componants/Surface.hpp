#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include "Device.hpp"
#include <vulkan/vulkan_core.h>
#if __has_include(<windows.h>)
#    include <Windows.h>
#    include <vulkan/vulkan_win32.h>
#endif
#if __has_include(<xcb/xcb.h>)
#    include <xcb/xcb.h>
#    include <vulkan/vulkan_xcb.h>

struct xcbContext
{
    xcb_connection_t *con;
    xcb_window_t win;
};

#endif
namespace LunaLux
{
// this is used as a handler for the vulkan window surface
class Surface
{
    // this is a pointer of the wrap for the device
    Device *dev = nullptr;
    // this is a memory pointer to the window surface
    VkSurfaceKHR surface = nullptr;
    // this is a memory pointer to the surface capabilities
    VkSurfaceCapabilitiesKHR surfaceCapabilities{};
    // this is a memory pointer to the surface format
    VkSurfaceFormatKHR surfaceFormat{};
    // this is used to store the present family index
    uint32_t present_family_index = 0;
    // this is a memory pointer to the program present queue
    VkQueue present_queue = nullptr;
    // this is a memory pointer to the program graphics queue
    VkQueue graphics_queue = nullptr;
    // this is used to find and chose the surface format
    static VkSurfaceFormatKHR pick_surface_format(std::vector<VkSurfaceFormatKHR> surfaceFormats)
    {
        // we loop though the vector until we find the surface format
        for (auto &item : surfaceFormats)
        {
            // if we find our preferred format use it
            if (item.format == VK_FORMAT_R8G8B8A8_UNORM || item.format == VK_FORMAT_B8G8R8A8_UNORM ||
                item.format == VK_FORMAT_R16G16B16A16_SFLOAT || item.format == VK_FORMAT_A2R10G10B10_UNORM_PACK32 ||
                item.format == VK_FORMAT_A2B10G10R10_UNORM_PACK32)
            {
                return item;
            }
        }
        // if we get here them we will fall back to the first format on the list
        printf("LunaLuxVulkanLib: Can't find our preferred formats... Falling back to first exposed format. Rendering "
               "may be incorrect.\n");
        return surfaceFormats[0];
    }

    // this is how we can create a surface it is not in the construct because if the surface is lost we need to recreate it
    void create(void *native_handle)
    {
        //if we are building on a windows platform then used the option to create a Win32 window Surface
#if __has_include(<windows.h>)
        VkWin32SurfaceCreateInfoKHR surface_info = {};
        surface_info.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        surface_info.hinstance = GetModuleHandle(nullptr);
        // this makes it only support one screen will need to find a better way to deal with this
        surface_info.hwnd = static_cast<HWND>(native_handle);
        //we ask the windows server to give use a graphics surface to work with
        TEST(vkCreateWin32SurfaceKHR,(dev->getInst()->get(), &surface_info, nullptr, &surface));
#endif
#if __has_include(<xcb/xcb.h>)
        xcbContext* context = reinterpret_cast<xcbContext*>(native_handle);
        VkXcbSurfaceCreateInfoKHR surface_info;
        surface_info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
        surface_info.pNext = NULL;
        surface_info.flags = 0;
        surface_info.connection = context->con;
        surface_info.window = context->win;

        TEST(vkCreateXcbSurfaceKHR,(dev->getInst()->get(), &surface_info, nullptr, &surface));
#endif
        //we check if the surface create is supported for the physical device we are using
        VkBool32 support{false};
        TEST(vkGetPhysicalDeviceSurfaceSupportKHR,(dev->getPDev(), dev->getFamilyIndex(), surface, &support));
        if (!support)
        {
            //if we don't then something has gone wrong during the creation of the vulkan Surface
            throw std::runtime_error("LunaLuxVulkanEngine: something is not right with surface creation");
        }
        //if we pass the check then we ask vulkan to get the Physical Device's surface capabilities
        TEST(vkGetPhysicalDeviceSurfaceCapabilitiesKHR,(dev->getPDev(), surface, &surfaceCapabilities));

        //we also ask vulkan to get the Physical Device's surface available formats
        uint32_t count = 0;
        TEST(vkGetPhysicalDeviceSurfaceFormatsKHR,(dev->getPDev(), surface, &count, nullptr));
        if (count == 0)
        {
            //if we fail to find any formats then something is wrong and the program should not continue
            throw std::runtime_error("no surface formats found");
        }
        //we ask vulkan to get the Physical Device's surface available formats again so we can put them into a vector
        std::vector<VkSurfaceFormatKHR> formats(count);
        TEST(vkGetPhysicalDeviceSurfaceFormatsKHR,(dev->getPDev(), surface, &count, formats.data()));
        //now we find the right format supported for our needs
        surfaceFormat = pick_surface_format(formats);
        // used to iterate and find the family index
        uint32_t i = 0;
        //we loop through the family queues to find the present queue used to draw to the screen
        //on some platforms the Present Queue and the Graphics Queue are separated
        for (const auto &queueFamily : dev->getQueues())
        {
            VkBool32 presentSupport = false;
            TEST(vkGetPhysicalDeviceSurfaceSupportKHR,(dev->getPDev(), i, surface, &presentSupport));
            if (presentSupport)present_family_index = i;
        }
        //after we fined the present_family_index we ask vulkan to get use a pointer to the Graphics queue in memory
        vkGetDeviceQueue(dev->getDev(), dev->getFamilyIndex(), 0, &graphics_queue);
        if (present_family_index != dev->getFamilyIndex())
        {
            //if the present_family_index is not the same as the graphics_family_index we ask vulkan to get use a pointer to the Present queue in memory
            vkGetDeviceQueue(dev->getDev(), present_family_index, 0, &present_queue);
            //we leave the create function
            return;
        }
        //if we get here means that present_family_index is the same as the graphics_family_index,
        // so we set the Present Queue pointer to the same as the Graphics
        present_queue = graphics_queue;
    }

    // this is how we can destroy a surface it is not in the deconstruct because if the surface is lost we need to recreate it
    void destroy()
    {
        // we tell the vulkan drive to destroy the vulkan window surface
        vkDestroySurfaceKHR(dev->getInst()->get(), surface, nullptr);
    }

  public:
    //used on class creation
    explicit Surface(Device *device, void *native_handle)
        : dev(device)
    {
        create(native_handle);
    }

    //this is used to recreate the Vulkan Surface if the Surface is lost some how
    void reset(void *native_handle)
    {
        destroy();
        create(native_handle);
    }

    //call when class pointer go's out of scope
    ~Surface()
    {
        destroy();
    }

    // this is to get the Present Queue
    [[nodiscard]] VkQueue getPresentQueue() const noexcept
    {
        return present_queue;
    }

    // this is to get the Graphics Queue
    [[nodiscard]] VkQueue getGraphicsQueue() const noexcept
    {
        return graphics_queue;
    }

    // this is to get the Vulkan Surface memory pointer
    [[nodiscard]] VkSurfaceKHR getSurface() const
    {
        return surface;
    }

    // this is to get the Vulkan Surface Capabilities
    [[nodiscard]] VkSurfaceCapabilitiesKHR getSurfaceCapabilities() const noexcept
    {
        return surfaceCapabilities;
    }

    // this is to get the chose Surface Format
    [[nodiscard]] VkSurfaceFormatKHR getSurfaceFormat() const noexcept
    {
        return surfaceFormat;
    }

    //this is to get the Vulkan Present Family Index
    [[nodiscard]] uint32_t getPresentFamilyIndex() const noexcept
    {
        return present_family_index;
    }
};
}; // namespace LunaLux