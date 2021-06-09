#pragma once
//
// Created by luket on 09/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <LunaLux/VulkanUtilLib.h>
// TODO: write documentation
namespace LunaLux
{
class Semaphore
{
    VkSemaphore semaphore;
  public:
    explicit Semaphore()
    {
        VkSemaphoreCreateInfo semaphoreInfo = vulkanCreateSemaphoreInfo(0);
        LunaLux::vkCreateSemaphore(&semaphoreInfo, &semaphore);
    }

    VkSemaphore the()
    {
        return semaphore;
    }

    void clear()
    {
        vkDestroySemaphore(semaphore);
    }
};
}
