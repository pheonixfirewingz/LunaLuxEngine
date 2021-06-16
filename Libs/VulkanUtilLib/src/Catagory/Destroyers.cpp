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

void vkDestroyImage(VkImage image)
{
    vkDestroyImage(vulkanGetDevice(), image, nullptr);
}

void vkDestroyImageView(VkImageView imageView)
{
    vkDestroyImageView(vulkanGetDevice(),imageView, nullptr);
}

void vkDestroySampler(VkSampler sampler)
{
    vkDestroySampler(vulkanGetDevice(), sampler, nullptr);
}

void vkDestroySemaphore(VkSemaphore semaphore)
{
    vkDestroySemaphore(vulkanGetDevice(),semaphore, nullptr);
}

void vkFreeCommandBuffers(VkCommandPool commandPool, uint32_t commandBufferCount,const VkCommandBuffer* pCommandBuffers)
{
    vkFreeCommandBuffers(vulkanGetDevice(),commandPool,commandBufferCount, pCommandBuffers);
}

void vkFreeMemory(VkDeviceMemory mem)
{
    vkFreeMemory(vulkanGetDevice(),mem, nullptr);
}

void vkDestroyBuffer(VkBuffer buffer)
{
    vkDestroyBuffer(vulkanGetDevice(),buffer, nullptr);
}

void vkDestroyFence(VkFence fence)
{
    vkDestroyFence(vulkanGetDevice(),fence, nullptr);
}

void vulkanDestroyGraphicsPipeline(vulkanPipeline *pipeline)
{
    vkDestroyPipeline(vulkanGetDevice(), pipeline->pipeline, nullptr);
    vkDestroyPipelineCache(vulkanGetDevice(), pipeline->pipelineCache, nullptr);
}

void vkDestroyShaderModule(VkShaderModule module)
{
    vkDestroyShaderModule(vulkanGetDevice(), module, nullptr);
}

void vkDestroyCommandPool(VkCommandPool commandPool)
{
    vkDestroyCommandPool(vulkanGetDevice(),commandPool, nullptr);
}

void vkDestroyFramebuffer(VkFramebuffer framebuffer)
{
    vkDestroyFramebuffer(vulkanGetDevice(),framebuffer, nullptr);
}

void vkDestroyDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout)
{
    vkDestroyDescriptorSetLayout(vulkanGetDevice(), descriptorSetLayout, nullptr);
}

void vkDestroyRenderPass(VkRenderPass renderPass)
{
    vkDestroyRenderPass(vulkanGetDevice(),renderPass, nullptr);
}

void vkDestroyPipelineLayout(VkPipelineLayout pipelineLayout)
{
    vkDestroyPipelineLayout(vulkanGetDevice(),pipelineLayout, nullptr);
}

void vkDestroyDescriptorPool(VkDescriptorPool descriptorPool)
{
    vkDestroyDescriptorPool(vulkanGetDevice(),descriptorPool,nullptr);
}
}