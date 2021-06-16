#pragma once
//
// Created by luket on 05/04/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#if __has_include(<windows.h>)
#    ifndef LIB_APP
#        define LLVUL_EXPORT __declspec(dllexport)
#    else
#        define LLVUL_EXPORT __declspec(dllimport)
#    endif
#endif
// TODO: write documentation
#include <vulkan/vulkan_core.h>
#include <vector>
namespace LunaLux
{
struct vulkanPipeline
{
    VkPipeline pipeline;
    VkPipelineCache pipelineCache;
};
//temp
LLVUL_EXPORT VkDevice vulkanUtilGetDevice();
//code cleaners
//used to make the code less cluttered
LLVUL_EXPORT VkImageCreateInfo vulkanCreateImageInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkSamplerCreateInfo vulkanCreateSamplerInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkBufferCreateInfo vulkanCreateUniformBufferInfo(uint32_t flags, size_t size) noexcept;
LLVUL_EXPORT VkAttachmentReference vulkanCreateColourAttRef(uint32_t pos) noexcept;
LLVUL_EXPORT VkAttachmentReference vulkanCreateDepthStencilAttRef(uint32_t pos) noexcept;
LLVUL_EXPORT VkRenderPassCreateInfo vulkanCreateRenderPassInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkShaderModuleCreateInfo vulkanCreateShaderModuleInfo(const uint32_t *code, size_t size) noexcept;
LLVUL_EXPORT VkPipelineInputAssemblyStateCreateInfo vulkanCreateInputAssemblyStateInfo(uint32_t flags);
LLVUL_EXPORT VkPipelineVertexInputStateCreateInfo vulkanCreateVertexInputStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineRasterizationStateCreateInfo vulkanCreateRasterizationStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineColorBlendStateCreateInfo vulkanCreateColorBlendStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineDepthStencilStateCreateInfo vulkanCreateDepthStencilStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineDynamicStateCreateInfo vulkanCreateDynamicStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineViewportStateCreateInfo vulkanCreateViewportStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineMultisampleStateCreateInfo vulkanCreateMultisampleStateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkGraphicsPipelineCreateInfo vulkanCreatePipelineInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkDescriptorPoolCreateInfo vulkanCreateDescriptorPoolInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkDescriptorSetAllocateInfo vulkanCreateDescriptorSetAllocateInfo() noexcept;
LLVUL_EXPORT VkCommandPoolCreateInfo vulkanCreateCommandPoolCreateInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPipelineLayoutCreateInfo vulkanCreatePipelineLayoutInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkSemaphoreCreateInfo vulkanCreateSemaphoreInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkFenceCreateInfo vulkanCreateFenceInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkDescriptorSetLayoutCreateInfo vulkanCreateDescriptorSetLayoutInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkPresentInfoKHR vulkanCreatePresentInfo() noexcept;
LLVUL_EXPORT VkImageMemoryBarrier vulkanCreateImageMemoryBarrier() noexcept;
LLVUL_EXPORT VkCommandBufferBeginInfo vulkanCreateCommandBufferBeginInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkImageViewCreateInfo vulkanImageViewInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkRenderPassBeginInfo vulkanCreateRenderPassBeginInfo() noexcept;
LLVUL_EXPORT VkFramebufferCreateInfo vulkanCreateFramebufferInfo(uint32_t flags) noexcept;
LLVUL_EXPORT VkCommandBufferAllocateInfo vulkanCreateCommandBufferAllocateInfo() noexcept;

//custom pipeline functions
LLVUL_EXPORT VkResult vulkanCreateGraphicsPipeline(const VkGraphicsPipelineCreateInfo* pCreateInfos, vulkanPipeline* pipeline);
LLVUL_EXPORT void vulkanDestroyGraphicsPipeline(vulkanPipeline* pipeline);
LLVUL_EXPORT void vkCmdBindGraphicPipeline(VkCommandBuffer commandBuffer, vulkanPipeline* pipeline);

//vulkan command wrappers
LLVUL_EXPORT VkResult vkCreateFence(const VkFenceCreateInfo* pCreateInfo,VkFence* pFence);
LLVUL_EXPORT VkResult vkCreateSemaphore(const VkSemaphoreCreateInfo* pCreateInfo,VkSemaphore* pSemaphore);
LLVUL_EXPORT VkResult vkCreateCommandPool(const VkCommandPoolCreateInfo* pCreateInfo,VkCommandPool* pCommandPool);
LLVUL_EXPORT void vkDeviceWaitIdle();
LLVUL_EXPORT VkResult vkWaitForFences(uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll,uint64_t timeout);
LLVUL_EXPORT void vkUpdateDescriptorSets(uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites,
                                         uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies);
LLVUL_EXPORT void vkUnmapMemory(VkDeviceMemory memory);
LLVUL_EXPORT void vkDestroyRenderPass(VkRenderPass renderPass);
LLVUL_EXPORT void vkDestroyDescriptorPool(VkDescriptorPool descriptorPool);
LLVUL_EXPORT void vkDestroyPipelineLayout(VkPipelineLayout pipelineLayout);
LLVUL_EXPORT void vkDestroyDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
LLVUL_EXPORT void vkDestroyCommandPool(VkCommandPool commandPool);
LLVUL_EXPORT void vkDestroyImage(VkImage image);
LLVUL_EXPORT void vkDestroyImageView(VkImageView imageView);
LLVUL_EXPORT void vkDestroySampler(VkSampler sampler);
LLVUL_EXPORT void vkDestroyFramebuffer(VkFramebuffer framebuffer);
LLVUL_EXPORT void vkDestroyShaderModule(VkShaderModule module);
LLVUL_EXPORT void vkFreeCommandBuffers(VkCommandPool commandPool,uint32_t commandBufferCount,const VkCommandBuffer* pCommandBuffers);
LLVUL_EXPORT void vkDestroySemaphore(VkSemaphore semaphore);
LLVUL_EXPORT void vkFreeMemory(VkDeviceMemory mem);
LLVUL_EXPORT void vkDestroyBuffer(VkBuffer buffer);
LLVUL_EXPORT void vkDestroyFence(VkFence fence);
} // namespace LunaLux
