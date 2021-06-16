#include "../API/VulkanUtilLib.h"
//
// Created by luket on 27/05/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
namespace LunaLux
{
VkImageCreateInfo vulkanCreateImageInfo(const uint32_t flags) noexcept
{
    VkImageCreateInfo image_create_info;
    image_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    image_create_info.pNext = nullptr;
    image_create_info.flags = flags;
    return image_create_info;
}

VkSamplerCreateInfo vulkanCreateSamplerInfo(const uint32_t flags) noexcept
{
    VkSamplerCreateInfo sampler{};
    sampler.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    sampler.pNext = nullptr;
    sampler.flags = flags;
    return sampler;
}

VkBufferCreateInfo vulkanCreateUniformBufferInfo(const uint32_t flags,const size_t size) noexcept
{
    VkBufferCreateInfo buf_info{};
    buf_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    buf_info.flags = flags;
    buf_info.usage = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
    buf_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    buf_info.size = size;
    return buf_info;
}

VkAttachmentReference vulkanCreateColourAttRef(const uint32_t pos) noexcept
{
    VkAttachmentReference color_reference;
    color_reference.attachment = pos;
    color_reference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    return color_reference;
}

VkAttachmentReference vulkanCreateDepthStencilAttRef(const uint32_t pos) noexcept
{
    VkAttachmentReference depth_reference;
    depth_reference.attachment = pos;
    depth_reference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    return depth_reference;
}

VkRenderPassCreateInfo vulkanCreateRenderPassInfo(const uint32_t flags) noexcept
{
    VkRenderPassCreateInfo rp_info;
    rp_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    rp_info.pNext = nullptr;
    rp_info.flags = flags;
    return rp_info;
}

VkShaderModuleCreateInfo vulkanCreateShaderModuleInfo(const uint32_t* code, const size_t size) noexcept
{
    VkShaderModuleCreateInfo moduleCreateInfo;
    moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    moduleCreateInfo.pNext = nullptr;
    moduleCreateInfo.flags = 0;
    moduleCreateInfo.codeSize = size;
    moduleCreateInfo.pCode = code;
    return moduleCreateInfo;
}

VkPipelineVertexInputStateCreateInfo vulkanCreateVertexInputStateInfo(const uint32_t flags) noexcept
{
    VkPipelineVertexInputStateCreateInfo vi{};
    vi.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vi.pNext = nullptr;
    vi.flags = flags;
    return vi;
}

VkPipelineInputAssemblyStateCreateInfo vulkanCreateInputAssemblyStateInfo(const uint32_t flags)
{
    VkPipelineInputAssemblyStateCreateInfo ia{};
    ia.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    ia.pNext = nullptr;
    ia.flags = flags;
    return ia;
}

VkPipelineRasterizationStateCreateInfo vulkanCreateRasterizationStateInfo(const uint32_t flags) noexcept
{
    VkPipelineRasterizationStateCreateInfo rs{};
    rs.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rs.pNext = nullptr;
    rs.flags = flags;
    return rs;
}

VkGraphicsPipelineCreateInfo vulkanCreatePipelineInfo(const uint32_t flags) noexcept
{
    VkGraphicsPipelineCreateInfo pipeline{};
    pipeline.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipeline.pNext = nullptr;
    pipeline.flags = flags;
    return pipeline;
}

VkPipelineColorBlendStateCreateInfo vulkanCreateColorBlendStateInfo(uint32_t flags) noexcept
{
    VkPipelineColorBlendStateCreateInfo cb{};
    cb.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    cb.pNext = nullptr;
    cb.flags = flags;
    return cb;
}

VkPipelineDepthStencilStateCreateInfo vulkanCreateDepthStencilStateInfo(uint32_t flags) noexcept
{
    VkPipelineDepthStencilStateCreateInfo ds{};
    ds.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    ds.pNext = nullptr;
    ds.flags = flags;
    return ds;
}

VkPipelineDynamicStateCreateInfo vulkanCreateDynamicStateInfo(uint32_t flags) noexcept
{
    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.pNext = nullptr;
    dynamicState.flags = flags;
    return dynamicState;
}

VkPipelineViewportStateCreateInfo vulkanCreateViewportStateInfo(uint32_t flags) noexcept
{
    VkPipelineViewportStateCreateInfo vp{};
    vp.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    vp.pNext = nullptr;
    vp.flags = flags;
    return vp;
}

VkPipelineMultisampleStateCreateInfo vulkanCreateMultisampleStateInfo(uint32_t flags) noexcept
{
    VkPipelineMultisampleStateCreateInfo ms{};
    ms.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    ms.pNext = nullptr;
    ms.flags = flags;
    return ms;
}

VkDescriptorPoolCreateInfo vulkanCreateDescriptorPoolInfo(uint32_t flags) noexcept
{
    VkDescriptorPoolCreateInfo descriptor_pool;
    descriptor_pool.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    descriptor_pool.pNext = nullptr;
    descriptor_pool.flags = flags;
    return descriptor_pool;
}

VkDescriptorSetAllocateInfo vulkanCreateDescriptorSetAllocateInfo() noexcept
{
    VkDescriptorSetAllocateInfo alloc_info;
    alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    alloc_info.pNext = nullptr;
    return alloc_info;
}

VkCommandPoolCreateInfo vulkanCreateCommandPoolCreateInfo(uint32_t flags) noexcept
{
    VkCommandPoolCreateInfo cmd_pool_info;
    cmd_pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    cmd_pool_info.pNext = nullptr;
    cmd_pool_info.flags = flags;
    return cmd_pool_info;
}

VkPresentInfoKHR vulkanCreatePresentInfo() noexcept
{
    VkPresentInfoKHR present;
    present.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    present.pNext = nullptr;
    return present;
}

VkPipelineLayoutCreateInfo vulkanCreatePipelineLayoutInfo(uint32_t flags) noexcept
{
    VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo;
    pPipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pPipelineLayoutCreateInfo.pNext = nullptr;
    pPipelineLayoutCreateInfo.flags = flags;
    return pPipelineLayoutCreateInfo;
}

VkSemaphoreCreateInfo vulkanCreateSemaphoreInfo(uint32_t flags) noexcept
{
    VkSemaphoreCreateInfo semaphoreCreateInfo;
    semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    semaphoreCreateInfo.pNext = nullptr;
    semaphoreCreateInfo.flags = flags;
    return semaphoreCreateInfo;
}

VkFenceCreateInfo vulkanCreateFenceInfo(uint32_t flags) noexcept
{
    VkFenceCreateInfo fence_ci;
    fence_ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fence_ci.pNext = nullptr;
    fence_ci.flags = flags;
    return fence_ci;
}

VkDescriptorSetLayoutCreateInfo vulkanCreateDescriptorSetLayoutInfo(uint32_t flags) noexcept
{
    VkDescriptorSetLayoutCreateInfo descriptor_layout;
    descriptor_layout.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    descriptor_layout.pNext = nullptr;
    descriptor_layout.flags = flags;
    return descriptor_layout;
}

VkImageMemoryBarrier vulkanCreateImageMemoryBarrier() noexcept
{
    VkImageMemoryBarrier image_ownership_barrier;
    image_ownership_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    image_ownership_barrier.pNext = nullptr;
    return image_ownership_barrier;
}

VkCommandBufferBeginInfo vulkanCreateCommandBufferBeginInfo(uint32_t flags) noexcept
{
    VkCommandBufferBeginInfo cmd_buf_info;
    cmd_buf_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    cmd_buf_info.pNext = nullptr;
    cmd_buf_info.flags = flags;
    return cmd_buf_info;
}

VkImageViewCreateInfo vulkanImageViewInfo(uint32_t flags) noexcept
{
    VkImageViewCreateInfo view;
    view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view.pNext = nullptr;
    view.flags = flags;
    return view;
}

VkRenderPassBeginInfo vulkanCreateRenderPassBeginInfo() noexcept
{
    VkRenderPassBeginInfo rp_begin;
    rp_begin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    rp_begin.pNext = nullptr;
    return rp_begin;
}

VkFramebufferCreateInfo vulkanCreateFramebufferInfo(uint32_t flags) noexcept
{
    VkFramebufferCreateInfo fb_info;
    fb_info.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    fb_info.pNext = nullptr;
    fb_info.flags = flags;
    return fb_info;
}

VkCommandBufferAllocateInfo vulkanCreateCommandBufferAllocateInfo() noexcept
{
    VkCommandBufferAllocateInfo cmd;
    cmd.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    cmd.pNext = nullptr;
    return cmd;
}


}