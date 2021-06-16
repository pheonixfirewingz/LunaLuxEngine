//
// Created by luket on 07/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "../API/VulkanUtilLib.h"
#include <LunaLux/VulkanLib.h>
namespace LunaLux
{
VkResult vulkanCreateGraphicsPipeline(const VkGraphicsPipelineCreateInfo *pCreateInfos, vulkanPipeline *pipeline)
{
    VkPipelineCacheCreateInfo pipelineCache{};
    pipelineCache.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    pipelineCache.flags = 0;

    VkResult err = vkCreatePipelineCache(LunaLux::vulkanGetDevice(), &pipelineCache, nullptr, &pipeline->pipelineCache);
    if(err != VK_SUCCESS)
    {
        return err;
    }
    err = vkCreateGraphicsPipelines(LunaLux::vulkanGetDevice(), pipeline->pipelineCache, 1, pCreateInfos, nullptr,&pipeline->pipeline);
    if(err != VK_SUCCESS)
    {
        return err;
    }
    return VK_SUCCESS;
}

VkResult vkCreateCommandPool(const VkCommandPoolCreateInfo *pCreateInfo, VkCommandPool *pCommandPool)
{
    return vkCreateCommandPool(LunaLux::vulkanGetDevice(), pCreateInfo, nullptr, pCommandPool);
}

VkResult vkCreateFence(const VkFenceCreateInfo *pCreateInfo, VkFence *pFence)
{
    return vkCreateFence(LunaLux::vulkanGetDevice(), pCreateInfo, nullptr, pFence);
}

VkResult vkCreateSemaphore(const VkSemaphoreCreateInfo *pCreateInfo, VkSemaphore *pSemaphore)
{
    return vkCreateSemaphore(LunaLux::vulkanGetDevice(), pCreateInfo, nullptr, pSemaphore);
}

}