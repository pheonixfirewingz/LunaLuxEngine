// TODO: this code is still being changed
#include "Device.hpp"
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <cassert>

void LunaLux::Device::findRightPhysicalDevice()
{
    uint32_t p_count = 0;
    TEST(vkEnumeratePhysicalDevices,(inst->get(), &p_count, nullptr));
    std::vector<VkPhysicalDevice> devices;
    devices.resize(p_count);
    TEST(vkEnumeratePhysicalDevices,(inst->get(), &p_count, devices.data()));

    std::vector<VkPhysicalDevice> devicesUsable;
    devices.resize(p_count);

    for (VkPhysicalDevice dev : devices)
    {
        if (usedPhysicalDevice(dev))
        {
            devicesUsable.push_back(dev);
        }
    }

    assert(devicesUsable.size() != 0);
    if (devicesUsable.size() == 1)
    {
        p_device = devicesUsable[0];
        vkGetPhysicalDeviceProperties(p_device, &properties);
        vkGetPhysicalDeviceFeatures(p_device, &features);
        return;
    }
    throw std::runtime_error("VULKAN_RUNTIME_FAILURE: multi gpu not supported!");
}

bool LunaLux::Device::usedPhysicalDevice(VkPhysicalDevice in_device)
{
    VkPhysicalDeviceProperties l_properties;
    vkGetPhysicalDeviceProperties(in_device, &l_properties);

    if (VK_VERSION_MAJOR(l_properties.apiVersion) > 1 || VK_VERSION_MINOR(l_properties.apiVersion) > 2)
        return false;
    if (l_properties.limits.maxImageDimension2D < 4096)
        return false;

    return true;
}
