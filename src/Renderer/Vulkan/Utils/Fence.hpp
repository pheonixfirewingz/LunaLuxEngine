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
class Fence
{
    VkFence fence;
  public:
    explicit Fence(uint32_t flags)
    {
        VkFenceCreateInfo fence_ci = vulkanCreateFenceInfo(flags);
        vkCreateFence(&fence_ci, &fence);
    }

    void waitFor()
    {
        vkWaitForFences(1, &fence, VK_TRUE, UINT64_MAX);
    }

    void Reset()
    {
        vkResetFences(vulkanUtilGetDevice(), 1, &fence);
    }

    VkFence the()
    {
        return fence;
    }

    void clear()
    {
        vkDestroyFence(fence);
    }
};
}
