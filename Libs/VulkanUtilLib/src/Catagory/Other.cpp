#include "../API/VulkanUtilLib.h"
#include <LunaLux/VulkanLib.h>
//
// Created by luket on 27/05/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
namespace LunaLux
{
void vkDeviceWaitIdle()
{
    vkDeviceWaitIdle(vulkanGetDevice());
}

void vkCmdBindGraphicPipeline(VkCommandBuffer commandBuffer, vulkanPipeline* pipeline)
{
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->pipeline);
}

void vkUpdateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites,
                            uint32_t descriptorCopyCount, const VkCopyDescriptorSet *pDescriptorCopies)
{
    vkUpdateDescriptorSets(vulkanGetDevice(), descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

VkResult vkWaitForFences(uint32_t fenceCount, const VkFence *pFences, VkBool32 waitAll, uint64_t timeout)
{
    return vkWaitForFences(LunaLux::vulkanGetDevice(), fenceCount, pFences, waitAll, timeout);
}

void vkUnmapMemory(VkDeviceMemory memory)
{
    vkUnmapMemory(vulkanGetDevice(),memory);
}

VkDevice vulkanUtilGetDevice()
{
    return vulkanGetDevice();
}

}