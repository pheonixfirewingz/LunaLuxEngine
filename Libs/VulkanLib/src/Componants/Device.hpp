#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <stdexcept>
#include <vector>
#include <vulkan/vulkan_core.h>
#include "Validator.h"

namespace LunaLux
{
// this is used as a handler for the vulkan instance, physical & logic devices
class Device
{
    // the vulkan instance is not need in many places so can just define it in the device class
    class Instance
    {
        // this is a memory pointer to the program instance
        VkInstance instance = nullptr;

      public:
        // this is the Instance class constructor this is called on class creation
        explicit Instance()
        {
            // this is the struct used to define the library application for the vulkan instance to read and identify
            // use in the vulkan driver
            VkApplicationInfo app_info{VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                       nullptr,
                                       "LunaLuxVulkanLib_app",
                                       VK_MAKE_VERSION(1, 0, 0),
                                       "LunaLux",
                                       VK_MAKE_VERSION(1, 0, 0),
                                       VK_API_VERSION_1_2};
            // this is used to store the extension names
#if __has_include(<xcb/xcb.h>)
            const char *extensions[] = {VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_xcb_surface"};
#endif
#if __has_include(<windows.h>)
            const char *extensions[] = {VK_KHR_SURFACE_EXTENSION_NAME, "VK_KHR_win32_surface"};
#endif

            // this is the struct used to tell the vulkan driver that we want a VkInstance and how we tell the debug
            // layers to active in our case we only will active the sdk validation layer to make sure the user compiles
            // with the vulkan specification
            VkInstanceCreateInfo inst_info{
                VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, nullptr, 0, &app_info, 0, nullptr, 2, extensions};
            // if the debug is enabled active debug layers
#if ENABLE_SPEC_VALIDATION == 1
                inst_info.enabledLayerCount = 1;
                // this const character pointer C array is used to store the text form of the debug layers used
                const char *debugLayers[1] = {"VK_LAYER_KHRONOS_validation"};
                inst_info.ppEnabledLayerNames = debugLayers;
#endif
            // this function asked the driver for an instance it takes in our instance struct and returns a VkInstance
            // memory pointer
           TEST(vkCreateInstance,(&inst_info, nullptr, &instance));
        }

        ~Instance()
        {
            // this function asked the driver to remove or instance from memory as we do not need it any more.
            vkDestroyInstance(instance, nullptr);
        }

        // this is used to get the memory pointer
        VkInstance get()
        {
            // returns instance memory
            return instance;
        }
    };

    // this is the definition of the wrap for the instance
    Instance *inst;
    // this is a memory pointer to the program physical device
    VkPhysicalDevice p_device{};
    // this is a memory pointer to the program device
    VkDevice device{};
    // this is a memory pointer to the program device memory properties
    VkPhysicalDeviceProperties properties{};
    // this is a memory pointer to the program device properties
    VkPhysicalDeviceMemoryProperties mem_properties{};
    // this is a memory pointer to the program device features
    VkFormatProperties form_properties{};
    // this is a memory pointer to the program device format properties
    VkPhysicalDeviceFeatures features{};
    // this is a unsigned int used to store the graphics family index
    uint32_t graphic_family_index;
    // this is a vector used to store the queue family's
    std::vector<VkQueueFamilyProperties> queueFamilies;

    // this function is used to see if the device is useful for the library
    static bool usedPhysicalDevice(VkPhysicalDevice in_device);

    // this function is used to find the right physic device
    void findRightPhysicalDevice();

  public:
    // this will be used to create the device
    explicit Device()
        : inst(new Instance())
    {
        // first we need to find the right Physical device
        findRightPhysicalDevice();
        // we extract the properties and Features of the chosen device
        vkGetPhysicalDeviceProperties(p_device, &properties);
        // FIXME: this makes the device class not as fluid as would like
        const VkFormat tex_format = VK_FORMAT_R8G8B8A8_UNORM;
        printf("LunaLuxVulkanLib: WARRING! -> vkGetPhysicalDeviceFormatProperties is static to "
               "VK_FORMAT_R8G8B8A8_UNORM for now");
        // we extract the properties and Format Properties of the chosen device
        vkGetPhysicalDeviceFormatProperties(p_device, tex_format, &form_properties);
        // we extract the properties and Features of the chosen device
        vkGetPhysicalDeviceMemoryProperties(p_device, &mem_properties);
        vkGetPhysicalDeviceFeatures(p_device, &features);
        // this is used to store the amount of family queues the Gpu has
        uint32_t queueFamilyCount = 0;
        // we ask vulkan to get the family queues
        vkGetPhysicalDeviceQueueFamilyProperties(p_device, &queueFamilyCount, nullptr);
        // we create a vector to store the family queues data structs
        queueFamilies.resize(queueFamilyCount);
        // we ask vulkan to get the family queues again
        vkGetPhysicalDeviceQueueFamilyProperties(p_device, &queueFamilyCount, queueFamilies.data());
        // used to iterate and find the Graphics family index
        uint32_t i = 0;
        // we loop through the vector to find the index
        for (const auto &queueFamily : queueFamilies)
        {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                graphic_family_index = i;
            }
            i++;
        }
        // we define the queue priority
        float queuePriority = 1.0f;
        // we create the queue info struct
        VkDeviceQueueCreateInfo queueCreateInfo{
            VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, nullptr, 0, graphic_family_index, 1, &queuePriority};
        // this vector is used to store the device extensions needed
        const std::vector<const char *> deviceExtensions = {VK_KHR_SWAPCHAIN_EXTENSION_NAME};
        // now we create the struct for to pass the data required for the dive to be created
        VkDeviceCreateInfo deviceCreateInfo{VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
                                            nullptr,
                                            0,
                                            1,
                                            &queueCreateInfo,
                                            0,
                                            nullptr,
                                            static_cast<uint32_t>(deviceExtensions.size()),
                                            deviceExtensions.data(),
                                            nullptr};
        // now we tell vulkan to create / allocate a device for use
        TEST(vkCreateDevice,(p_device, &deviceCreateInfo, nullptr, &device));
    }

    // this will be used to destroy the device
    ~Device()
    {
        // we tell vulkan that we are finished with the device and it can be deallocated from memory
        vkDestroyDevice(device, nullptr);
        // we zero the physic device accessor
        p_device = nullptr;
        // we delete our vulkan instance
        delete inst;
    }

    // this is here so the few places that need the instance can access it
    [[nodiscard]] Instance *getInst() const noexcept
    {
        return inst;
    }

    // this is used to find the memory of the gpu that is needed by the user
    [[nodiscard]] uint32_t findGpuMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags flags)
    {
        // first we create a struct of the GPU memory properties and ask vulkan for them
        VkPhysicalDeviceMemoryProperties memProperties;
        vkGetPhysicalDeviceMemoryProperties(p_device, &memProperties);

        // now we iterate through until we find the memory type we need
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
        {
            // we check if the flags and filter type match and return the index to it when found
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & flags) == flags)
                return i;
        }
        // if we reach here that is bad for now we throw a runtime error but this should have a fallback function for
        // the user to handle it in the future
        throw std::runtime_error("VULKAN_RUNTIME_FAILURE: failed to find suitable memory type!");
    }

    // this gets the device family queues
    std::vector<VkQueueFamilyProperties> getQueues() noexcept
    {
        return queueFamilies;
    }

    // this is to get the physical device
    [[nodiscard]] VkPhysicalDevice getPDev()
    {
        return p_device;
    }

    // this is to get the device
    [[nodiscard]] VkDevice getDev()
    {
        return device;
    }

    // this is used to get the index of the graphics family
    [[nodiscard]] uint32_t getFamilyIndex() const noexcept
    {
        return graphic_family_index;
    }

    // this is used to find the GPUs maximum available sample count
    [[maybe_unused]] [[nodiscard]] VkSampleCountFlagBits getMaxUsableSampleCount() const
    {
        VkSampleCountFlags counts =
            properties.limits.framebufferColorSampleCounts & properties.limits.framebufferDepthSampleCounts;
        if (counts & VK_SAMPLE_COUNT_64_BIT)
        {
            return VK_SAMPLE_COUNT_64_BIT;
        }
        if (counts & VK_SAMPLE_COUNT_32_BIT)
        {
            return VK_SAMPLE_COUNT_32_BIT;
        }
        if (counts & VK_SAMPLE_COUNT_16_BIT)
        {
            return VK_SAMPLE_COUNT_16_BIT;
        }
        if (counts & VK_SAMPLE_COUNT_8_BIT)
        {
            return VK_SAMPLE_COUNT_8_BIT;
        }
        if (counts & VK_SAMPLE_COUNT_4_BIT)
        {
            return VK_SAMPLE_COUNT_4_BIT;
        }
        if (counts & VK_SAMPLE_COUNT_2_BIT)
        {
            return VK_SAMPLE_COUNT_2_BIT;
        }
        return VK_SAMPLE_COUNT_1_BIT;
    }

    /* many not be needed we will see
    //this is to get the physical device properties
    [[nodiscard]] VkPhysicalDeviceProperties getProperties() const noexcept
    { return properties; }

    //this is to get the physical device features
    [[nodiscard]] VkPhysicalDeviceFeatures getDeviceFeatures() const noexcept
    { return features; }

    //this is to get the physical device memory properties
    [[nodiscard]] VkPhysicalDeviceMemoryProperties getMemProperties() const noexcept
    { return mem_properties; }*/

    // this is to get the physical device format properties
    [[nodiscard]] VkFormatProperties getFormProperties() const noexcept
    {
        return form_properties;
    }
};
}; // namespace LunaLux