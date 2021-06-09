#include "../src/API/VulkanUtilLib.h"
#include "linmath.hpp"
#include <LunaLux/KeyMap.h>
#include <LunaLux/VulkanLib.h>
#include <LunaLux/WindowLib.h>

#define DEMO_TEXTURE_COUNT 1
// Allow a maximum of two outstanding presentation operations.
#define FRAME_LAG 2

struct texture_object
{
    VkSampler sampler;
    VkImage image;
    VkBuffer buffer;
    VkImageLayout imageLayout;

    VkMemoryAllocateInfo mem_alloc;
    VkDeviceMemory mem;
    VkImageView view;
    int32_t tex_width, tex_height;
};

struct vkTextureCube_vs_uniform
{
    // Must start with MVP
    float mvp[4][4];
    [[maybe_unused]] float position[12 * 3][4];
    [[maybe_unused]] float attr[12 * 3][4];
};

static const float g_vertex_buffer_data[] = {
    -1.0f, -1.0f,
    -1.0f, // -X side
    -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,
    -1.0f, // -Z side
    1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f,
    -1.0f, -1.0f,
    -1.0f, // -Y side
    1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
    -1.0f, 1.0f,
    -1.0f, // +Y side
    -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
    1.0f,  1.0f,
    -1.0f, // +X side
    1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
    -1.0f, 1.0f,
    1.0f, // +Z side
    -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
};

static const float g_uv_buffer_data[] = {
    0.0f,
    1.0f, // -X side
    1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    1.0f, // -Z side
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.0f, // -Y side
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.0f, // +Y side
    0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    0.0f, // +X side
    0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    0.0f, // +Z side
    0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
};

typedef struct
{
    VkCommandBuffer cmd;
    VkCommandBuffer graphics_to_present_cmd;
    VkBuffer uniform_buffer;
    VkDeviceMemory uniform_memory;
    void *uniform_memory_ptr;
    VkFramebuffer frameBuffer;
    VkDescriptorSet descriptor_set;
} SwapChainImageResources;

struct m_demo
{
    bool prepared;
    bool use_staging_buffer;
    bool separate_present_queue;
    bool is_minimized;

    VkSemaphore image_acquired_semaphores[FRAME_LAG];
    VkSemaphore draw_complete_semaphores[FRAME_LAG];
    VkSemaphore image_ownership_semaphores[FRAME_LAG];

    SwapChainImageResources *swapChain_img_res;
    VkFence fences[FRAME_LAG];
    int frame_index;

    VkCommandPool cmd_pool;
    VkCommandPool present_cmd_pool;

    struct
    {
        VkFormat format;
        VkImage image;
        VkMemoryAllocateInfo mem_alloc;
        VkDeviceMemory mem;
        VkImageView view;
    } depth;

    texture_object textures[DEMO_TEXTURE_COUNT];
    texture_object staging_texture;

    VkCommandBuffer cmd; // Buffer for initialization commands
    LunaLux::vulkanPipeline pipeline;
    VkPipelineLayout pipeline_layout;
    VkDescriptorSetLayout desc_layout;
    VkRenderPass render_pass;

    mat4x4 projection_matrix;
    mat4x4 view_matrix;
    mat4x4 model_matrix;

    float spin_angle;

    VkShaderModule vert_shader_module;
    VkShaderModule frag_shader_module;

    VkDescriptorPool desc_pool;

    int32_t curFrame;
    int32_t frameCount;
    uint32_t current_buffer;
} m_demo;

// Forward declarations:
static void demo_resize();

static void demo_flush_init_cmd()
{
    if (m_demo.cmd == nullptr)
    {
        return;
    }
    vkEndCommandBuffer(m_demo.cmd);

    VkFence fence;
    VkFenceCreateInfo fence_ci = LunaLux::vulkanCreateFenceInfo(0);
    LunaLux::vkCreateFence(&fence_ci, &fence);

    const VkCommandBuffer cmd_buffers[] = {m_demo.cmd};
    VkSubmitInfo submit_info = {.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
        .pNext = nullptr,
        .waitSemaphoreCount = 0,
        .pWaitSemaphores = nullptr,
        .pWaitDstStageMask = nullptr,
        .commandBufferCount = 1,
        .pCommandBuffers = cmd_buffers,
        .signalSemaphoreCount = 0,
        .pSignalSemaphores = nullptr};

    vkQueueSubmit(LunaLux::vulkanGetGraphicsQueue(), 1, &submit_info, fence);

    LunaLux::vkWaitForFences(1, &fence, VK_TRUE, UINT64_MAX);

    LunaLux::vkFreeCommandBuffers(m_demo.cmd_pool, 1, cmd_buffers);
    LunaLux::vkDestroyFence(fence);
    m_demo.cmd = nullptr;
}

static void demo_set_image_layout(VkImage image, VkImageAspectFlags aspectMask, VkImageLayout old_image_layout,
                                  VkImageLayout new_image_layout, VkAccessFlagBits srcAccessMask,
                                  VkPipelineStageFlags src_stages, VkPipelineStageFlags destination_stages)
{
    VkImageMemoryBarrier image_memory_barrier;
    image_memory_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    image_memory_barrier.pNext = nullptr;
    image_memory_barrier.srcAccessMask = static_cast<VkAccessFlags>(srcAccessMask);
    image_memory_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    image_memory_barrier.oldLayout = old_image_layout;
    image_memory_barrier.newLayout = new_image_layout;
    image_memory_barrier.image = image;
    image_memory_barrier.subresourceRange = {aspectMask, 0, 1, 0, 1};

    switch (new_image_layout)
    {
    case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
        image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
        break;
    case VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL:
        image_memory_barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        break;
    case VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL:
        image_memory_barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
        break;
    case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
        image_memory_barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_INPUT_ATTACHMENT_READ_BIT;
        break;
    case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
        image_memory_barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
        break;
    case VK_IMAGE_LAYOUT_PRESENT_SRC_KHR:
        image_memory_barrier.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT;
        break;
    default:
        image_memory_barrier.dstAccessMask = 0;
        break;
    }

    vkCmdPipelineBarrier(m_demo.cmd, src_stages, destination_stages, 0, 0, nullptr, 0, nullptr, 1,
                         &image_memory_barrier);
}

static void demo_draw_build_cmd(VkCommandBuffer cmd_buf)
{
    VkCommandBufferBeginInfo cmd_buf_info = LunaLux::vulkanCreateCommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);
    cmd_buf_info.pInheritanceInfo = nullptr;

    VkClearValue clear_values[2];
    clear_values[0].color = {0.2f, 0.2f, 0.2f, 0.2f};
    clear_values[1].depthStencil = {1.0f, 0};

    VkRenderPassBeginInfo rp_begin = LunaLux::vulkanCreateRenderPassBeginInfo();
    rp_begin.renderPass = m_demo.render_pass;
    rp_begin.framebuffer = m_demo.swapChain_img_res[m_demo.current_buffer].frameBuffer;
    rp_begin.renderArea.offset = {0, 0};
    rp_begin.renderArea.extent.width = std::get<0>(LunaLux::GetWindowSize());
    rp_begin.renderArea.extent.height = std::get<1>(LunaLux::GetWindowSize());
    rp_begin.clearValueCount = 2;
    rp_begin.pClearValues = clear_values;

    vkBeginCommandBuffer(cmd_buf, &cmd_buf_info);

    vkCmdBeginRenderPass(cmd_buf, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);

    LunaLux::vkCmdBindGraphicPipeline(cmd_buf, &m_demo.pipeline);
    vkCmdBindDescriptorSets(cmd_buf, VK_PIPELINE_BIND_POINT_GRAPHICS, m_demo.pipeline_layout, 0, 1,
                            &m_demo.swapChain_img_res[m_demo.current_buffer].descriptor_set, 0, nullptr);
    VkViewport viewport{};
    float viewport_dimension;
    if (std::get<0>(LunaLux::GetWindowSize()) < std::get<1>(LunaLux::GetWindowSize()))
    {
        viewport_dimension = static_cast<float>(std::get<0>(LunaLux::GetWindowSize()));
        viewport.y =
            static_cast<float>(std::get<1>(LunaLux::GetWindowSize()) - std::get<0>(LunaLux::GetWindowSize())) / 2.0f;
    }
    else
    {
        viewport_dimension = static_cast<float>(std::get<1>(LunaLux::GetWindowSize()));
        viewport.x =
            static_cast<float>(std::get<0>(LunaLux::GetWindowSize()) - std::get<1>(LunaLux::GetWindowSize())) / 2.0f;
    }
    viewport.height = viewport_dimension;
    viewport.width = viewport_dimension;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(cmd_buf, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.extent.width = std::get<0>(LunaLux::GetWindowSize());
    scissor.extent.height = std::get<1>(LunaLux::GetWindowSize());
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    vkCmdSetScissor(cmd_buf, 0, 1, &scissor);
    vkCmdDraw(cmd_buf, 12 * 3, 1, 0, 0);
    vkCmdEndRenderPass(cmd_buf);

    if (m_demo.separate_present_queue)
    {
        VkImageMemoryBarrier image_ownership_barrier = LunaLux::vulkanCreateImageMemoryBarrier();
        image_ownership_barrier.srcAccessMask = 0;
        image_ownership_barrier.dstAccessMask = 0;
        image_ownership_barrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        image_ownership_barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
        image_ownership_barrier.srcQueueFamilyIndex = LunaLux::vulkanGetGraphicsFamilyIndex();
        image_ownership_barrier.dstQueueFamilyIndex = LunaLux::vulkanGetPresentFamilyIndex();
        image_ownership_barrier.image = LunaLux::vulkanGetSwapChainImages()[m_demo.current_buffer];
        image_ownership_barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

        vkCmdPipelineBarrier(cmd_buf, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0,
                             nullptr, 0, nullptr, 1, &image_ownership_barrier);
    }
    vkEndCommandBuffer(cmd_buf);
}

void demo_build_image_ownership_cmd(int i)
{
    VkCommandBufferBeginInfo cmd_buf_info = LunaLux::vulkanCreateCommandBufferBeginInfo(VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT);
    cmd_buf_info.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(m_demo.swapChain_img_res[i].graphics_to_present_cmd, &cmd_buf_info);

    VkImageMemoryBarrier image_ownership_barrier = LunaLux::vulkanCreateImageMemoryBarrier();
    image_ownership_barrier.srcAccessMask = 0;
    image_ownership_barrier.dstAccessMask = 0;
    image_ownership_barrier.oldLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    image_ownership_barrier.newLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    image_ownership_barrier.srcQueueFamilyIndex = LunaLux::vulkanGetGraphicsFamilyIndex();
    image_ownership_barrier.dstQueueFamilyIndex = LunaLux::vulkanGetPresentFamilyIndex();
    image_ownership_barrier.image = LunaLux::vulkanGetSwapChainImages()[i];
    image_ownership_barrier.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};

    vkCmdPipelineBarrier(m_demo.swapChain_img_res[i].graphics_to_present_cmd,VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
                         VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, 0, 0, nullptr, 0, nullptr, 1, &image_ownership_barrier);

    vkEndCommandBuffer(m_demo.swapChain_img_res[i].graphics_to_present_cmd);
}

void demo_update_data_buffer()
{
    mat4x4 MVP, Model, VP;

    mat4x4_mul(VP, m_demo.projection_matrix, m_demo.view_matrix);
    // Rotate around the Y axis
    mat4x4_dup(Model, m_demo.model_matrix);
    mat4x4_rotate(m_demo.model_matrix, Model, 0.0f, 1.0f, 0.0f, (float)degreesToRadians(m_demo.spin_angle));
    mat4x4_mul(MVP, VP, m_demo.model_matrix);

    memcpy(m_demo.swapChain_img_res[m_demo.current_buffer].uniform_memory_ptr, (const void *)&MVP[0][0],
           sizeof(MVP));
}

static void demo_draw()
{
    if (LunaLux::shouldCloseWindow())
    {
        return;
    }

    // Ensure no more than FRAME_LAG renderings are outstanding
    LunaLux::vkWaitForFences(1, &m_demo.fences[m_demo.frame_index], VK_TRUE, UINT64_MAX);
    vkResetFences(LunaLux::vulkanUtilGetDevice(), 1, &m_demo.fences[m_demo.frame_index]);

    VkResult err;
    do
    {
        // Get the index of the next available swapChain image:
        err = vkAcquireNextImageKHR(LunaLux::vulkanUtilGetDevice(), LunaLux::vulkanGetSwapChain(), UINT64_MAX,
                                    m_demo.image_acquired_semaphores[m_demo.frame_index], nullptr,
                                    &m_demo.current_buffer);

        if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
        {
            demo_resize();
        }
        else if (err == VK_ERROR_SURFACE_LOST_KHR)
        {
            LunaLux::vulkanRe_establishSurface(LunaLux::getNativeWindow());
            demo_resize();
        }
    } while (err != VK_SUCCESS);

    demo_update_data_buffer();

    VkPipelineStageFlags pipe_stage_flags;
    VkSubmitInfo submit_info;
    submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submit_info.pNext = nullptr;
    submit_info.pWaitDstStageMask = &pipe_stage_flags;
    pipe_stage_flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    submit_info.waitSemaphoreCount = 1;
    submit_info.pWaitSemaphores = &m_demo.image_acquired_semaphores[m_demo.frame_index];
    submit_info.commandBufferCount = 1;
    submit_info.pCommandBuffers = &m_demo.swapChain_img_res[m_demo.current_buffer].cmd;
    submit_info.signalSemaphoreCount = 1;
    submit_info.pSignalSemaphores = &m_demo.draw_complete_semaphores[m_demo.frame_index];
    vkQueueSubmit(LunaLux::vulkanGetGraphicsQueue(), 1, &submit_info, m_demo.fences[m_demo.frame_index]);

    if (m_demo.separate_present_queue)
    {
        VkFence nullFence = nullptr;
        pipe_stage_flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        submit_info.waitSemaphoreCount = 1;
        submit_info.pWaitSemaphores = &m_demo.draw_complete_semaphores[m_demo.frame_index];
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &m_demo.swapChain_img_res[m_demo.current_buffer].graphics_to_present_cmd;
        submit_info.signalSemaphoreCount = 1;
        submit_info.pSignalSemaphores = &m_demo.image_ownership_semaphores[m_demo.frame_index];
        vkQueueSubmit(LunaLux::vulkanGetPresentQueue(), 1, &submit_info, nullFence);
    }

    VkPresentInfoKHR present = LunaLux::vulkanCreatePresentInfo();
    present.waitSemaphoreCount = 1;
    present.pWaitSemaphores = (m_demo.separate_present_queue) ? &m_demo.image_ownership_semaphores[m_demo.frame_index]
                                                              : &m_demo.draw_complete_semaphores[m_demo.frame_index];

    VkSwapchainKHR swapChains[] = {LunaLux::vulkanGetSwapChain()};
    present.swapchainCount = 1;
    present.pSwapchains = swapChains;
    present.pImageIndices = &m_demo.current_buffer;
    present.pResults = nullptr;

    err = vkQueuePresentKHR(LunaLux::vulkanGetPresentQueue(), &present);
    m_demo.frame_index += 1;
    m_demo.frame_index %= FRAME_LAG;

    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR)
    {
        demo_resize();
    }
    else if (err == VK_ERROR_SURFACE_LOST_KHR)
    {
        LunaLux::vulkanRe_establishSurface(LunaLux::getNativeWindow());
        demo_resize();
    }
}

static void demo_prepare_buffers()
{
    if (std::get<0>(LunaLux::GetWindowSize()) == 0 || std::get<1>(LunaLux::GetWindowSize()) == 0)
    {
        m_demo.is_minimized = true;
        return;
    }
    else
    {
        m_demo.is_minimized = false;
    }
    m_demo.swapChain_img_res = new SwapChainImageResources[LunaLux::vulkanGetSwapChainImageCount()];
}

static void demo_prepare_depth()
{
    const VkFormat depth_format = VK_FORMAT_D16_UNORM;
    VkImageCreateInfo image = LunaLux::vulkanCreateImageInfo(0);
    image.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
    image.imageType = VK_IMAGE_TYPE_2D;
    image.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image.format = depth_format;
    image.extent = {static_cast<uint32_t>(std::get<0>(LunaLux::GetWindowSize())),
        static_cast<uint32_t>(std::get<1>(LunaLux::GetWindowSize())), 1};
    image.mipLevels = 1;
    image.arrayLayers = 1;
    image.samples = VK_SAMPLE_COUNT_1_BIT;
    image.tiling = VK_IMAGE_TILING_OPTIMAL;
    image.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;

    VkImageViewCreateInfo view;
    view.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    view.pNext = nullptr;
    view.image = nullptr;
    view.format = depth_format;
    view.subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1};
    view.components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
        VK_COMPONENT_SWIZZLE_IDENTITY};
    view.flags = 0;
    view.viewType = VK_IMAGE_VIEW_TYPE_2D;

    VkMemoryRequirements memoryRequirements;

    m_demo.depth.format = depth_format;

    /* create image */
    vkCreateImage(LunaLux::vulkanUtilGetDevice(), &image, nullptr, &m_demo.depth.image);

    vkGetImageMemoryRequirements(LunaLux::vulkanUtilGetDevice(), m_demo.depth.image, &memoryRequirements);

    m_demo.depth.mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    m_demo.depth.mem_alloc.pNext = nullptr;
    m_demo.depth.mem_alloc.allocationSize = memoryRequirements.size;
    m_demo.depth.mem_alloc.memoryTypeIndex =
        LunaLux::vulkanFindGpuMemoryType(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

    /* allocate memory */
    vkAllocateMemory(LunaLux::vulkanUtilGetDevice(), &m_demo.depth.mem_alloc, nullptr, &m_demo.depth.mem);

    /* bind memory */
    vkBindImageMemory(LunaLux::vulkanUtilGetDevice(), m_demo.depth.image, m_demo.depth.mem, 0);

    /* create image view */
    view.image = m_demo.depth.image;
    vkCreateImageView(LunaLux::vulkanUtilGetDevice(), &view, nullptr, &m_demo.depth.view);
}

/* Convert ppm image data from header file into RGBA texture image */
#include "lunarg.ppm.hpp"

bool loadTexture(uint8_t *rgba_data, VkSubresourceLayout *layout, int32_t *width, int32_t *height)
{
    char *cPtr;
    cPtr = (char *)lunarg_ppm;
    if ((unsigned char *)cPtr >= (lunarg_ppm + lunarg_ppm_len) || strncmp(cPtr, "P6\n", 3) != 0)
    {
        return false;
    }
    while (strncmp(cPtr++, "\n", 1) != 0)
        ;

    sscanf_s(cPtr, "%u %u", width, height);
    if (rgba_data == nullptr)
    {
        return true;
    }
    while (strncmp(cPtr++, "\n", 1) != 0)
        ;

    if ((unsigned char *)cPtr >= (lunarg_ppm + lunarg_ppm_len) || strncmp(cPtr, "255\n", 4) != 0)
    {
        return false;
    }
    while (strncmp(cPtr++, "\n", 1) != 0)
        ;

    for (int y = 0; y < *height; y++)
    {
        uint8_t *rowPtr = rgba_data;
        for (int x = 0; x < *width; x++)
        {
            memcpy(rowPtr, cPtr, 3);
            rowPtr[3] = 255; /* Alpha of 1 */
            rowPtr += 4;
            cPtr += 3;
        }
        rgba_data += layout->rowPitch;
    }
    return true;
}

static void demo_prepare_texture_buffer(texture_object *tex_obj)
{
    int32_t tex_width, tex_height;

    if (!loadTexture(nullptr, nullptr, &tex_width, &tex_height))
    {
        printf("failed to load texture");
        std::exit(-1);
    }

    tex_obj->tex_width = tex_width;
    tex_obj->tex_height = tex_height;
    const VkBufferCreateInfo buffer_create_info = {.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
        .pNext = nullptr,
        .flags = 0,
        .size = static_cast<VkDeviceSize>(tex_width * tex_height * 4),
        .usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .queueFamilyIndexCount = 0,
        .pQueueFamilyIndices = nullptr};

    vkCreateBuffer(LunaLux::vulkanUtilGetDevice(), &buffer_create_info, nullptr, &tex_obj->buffer);
    VkMemoryRequirements memoryRequirements;
    vkGetBufferMemoryRequirements(LunaLux::vulkanUtilGetDevice(), tex_obj->buffer, &memoryRequirements);

    tex_obj->mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    tex_obj->mem_alloc.pNext = nullptr;
    tex_obj->mem_alloc.allocationSize = memoryRequirements.size;
    VkFlags requirements = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
    tex_obj->mem_alloc.memoryTypeIndex =
        LunaLux::vulkanFindGpuMemoryType(memoryRequirements.memoryTypeBits, requirements);

    vkAllocateMemory(LunaLux::vulkanUtilGetDevice(), &tex_obj->mem_alloc, nullptr, &(tex_obj->mem));

    /* bind memory */
    vkBindBufferMemory(LunaLux::vulkanUtilGetDevice(), tex_obj->buffer, tex_obj->mem, 0);

    VkSubresourceLayout layout;
    layout.rowPitch = tex_width * 4;

    void *data;
    vkMapMemory(LunaLux::vulkanUtilGetDevice(), tex_obj->mem, 0, tex_obj->mem_alloc.allocationSize, 0, &data);

    if (!loadTexture(static_cast<uint8_t *>(data), &layout, &tex_width, &tex_height))
    {
        printf("Error loading texture\n");
    }
    LunaLux::vkUnmapMemory(tex_obj->mem);
}

static void demo_prepare_texture_image(texture_object *tex_obj, VkImageTiling tiling, VkImageUsageFlags usage,
                                       VkFlags req_props)
{
    const VkFormat tex_format = VK_FORMAT_R8G8B8A8_UNORM;
    int32_t tex_width, tex_height;

    if (!loadTexture(nullptr, nullptr, &tex_width, &tex_height))
    {
        printf("failed to load texture\n");
        std::exit(-1);
    }

    tex_obj->tex_width = tex_width;
    tex_obj->tex_height = tex_height;
    VkImageCreateInfo image_create_info = LunaLux::vulkanCreateImageInfo(0);
    image_create_info.imageType = VK_IMAGE_TYPE_2D;
    image_create_info.format = tex_format;
    image_create_info.extent = {static_cast<uint32_t>(tex_width), static_cast<uint32_t>(tex_height), 1};
    image_create_info.mipLevels = 1;
    image_create_info.arrayLayers = 1;
    image_create_info.samples = VK_SAMPLE_COUNT_1_BIT;
    image_create_info.tiling = tiling;
    image_create_info.usage = usage;
    image_create_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    image_create_info.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;

    VkMemoryRequirements memoryRequirements;

    vkCreateImage(LunaLux::vulkanUtilGetDevice(), &image_create_info, nullptr, &tex_obj->image);

    vkGetImageMemoryRequirements(LunaLux::vulkanUtilGetDevice(), tex_obj->image, &memoryRequirements);

    tex_obj->mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    tex_obj->mem_alloc.pNext = nullptr;
    tex_obj->mem_alloc.allocationSize = memoryRequirements.size;
    tex_obj->mem_alloc.memoryTypeIndex = LunaLux::vulkanFindGpuMemoryType(memoryRequirements.memoryTypeBits, req_props);

    /* allocate memory */
    vkAllocateMemory(LunaLux::vulkanUtilGetDevice(), &tex_obj->mem_alloc, nullptr, &(tex_obj->mem));

    /* bind memory */
    vkBindImageMemory(LunaLux::vulkanUtilGetDevice(), tex_obj->image, tex_obj->mem, 0);

    if (req_props & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        const VkImageSubresource subresource = {
            .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
            .mipLevel = 0,
            .arrayLayer = 0,
        };
        VkSubresourceLayout layout;
        void *data;

        vkGetImageSubresourceLayout(LunaLux::vulkanUtilGetDevice(), tex_obj->image, &subresource, &layout);

        vkMapMemory(LunaLux::vulkanUtilGetDevice(), tex_obj->mem, 0, tex_obj->mem_alloc.allocationSize, 0, &data);

        if (!loadTexture(static_cast<uint8_t *>(data), &layout, &tex_width, &tex_height))
        {
            printf("Error loading texture");
        }
        LunaLux::vkUnmapMemory(tex_obj->mem);
    }

    tex_obj->imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}

static void demo_destroy_texture(texture_object *textureObject)
{
    /* clean up staging resources */
    LunaLux::vkFreeMemory(textureObject->mem);
    if (textureObject->image)
    {
        LunaLux::vkDestroyImage(textureObject->image);
    }
    if (textureObject->buffer)
    {
        LunaLux::vkDestroyBuffer(textureObject->buffer);
    }
}

static void demo_prepare_textures()
{
    VkFormatProperties props = LunaLux::vulkanGetDeviceFormatProperties();

    for (auto &texture : m_demo.textures)
    {

        if ((props.linearTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT) && !m_demo.use_staging_buffer)
        {
            demo_prepare_texture_image(&texture, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_SAMPLED_BIT,
                                       VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

            demo_set_image_layout(texture.image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED,
                                  texture.imageLayout, static_cast<VkAccessFlagBits>(0),
                                  VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
            m_demo.staging_texture.image = nullptr;
        }
        else if (props.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT)
        {
            /* Must use staging buffer to copy linear texture to optimized */

            demo_prepare_texture_buffer(&m_demo.staging_texture);

            demo_prepare_texture_image(&texture, VK_IMAGE_TILING_OPTIMAL,
                                       (VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT),
                                       VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

            demo_set_image_layout(texture.image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_PREINITIALIZED,
                                  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, static_cast<VkAccessFlagBits>(0),
                                  VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

            VkBufferImageCopy copy_region = {
                .bufferOffset = 0,
                .bufferRowLength = static_cast<uint32_t>(m_demo.staging_texture.tex_width),
                .bufferImageHeight = static_cast<uint32_t>(m_demo.staging_texture.tex_height),
                .imageSubresource = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1},
                .imageOffset = {0, 0, 0},
                .imageExtent = {static_cast<uint32_t>(m_demo.staging_texture.tex_width),
                    static_cast<uint32_t>(m_demo.staging_texture.tex_height), 1},
            };

            vkCmdCopyBufferToImage(m_demo.cmd, m_demo.staging_texture.buffer, texture.image,
                                   VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copy_region);

            demo_set_image_layout(texture.image, VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                                  texture.imageLayout, VK_ACCESS_TRANSFER_WRITE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
                                  VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
        }

        VkSamplerCreateInfo sampler = LunaLux::vulkanCreateSamplerInfo(0);
        sampler.magFilter = VK_FILTER_NEAREST;
        sampler.minFilter = VK_FILTER_NEAREST;
        sampler.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
        sampler.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sampler.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sampler.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
        sampler.mipLodBias = 0.0f;
        sampler.anisotropyEnable = VK_FALSE;
        sampler.maxAnisotropy = 1;
        sampler.compareOp = VK_COMPARE_OP_NEVER;
        sampler.minLod = 0.0f;
        sampler.maxLod = 0.0f;
        sampler.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
        sampler.unnormalizedCoordinates = VK_FALSE;
        sampler.compareEnable = VK_FALSE;

        VkImageViewCreateInfo view = LunaLux::vulkanImageViewInfo(0);
        view.image = nullptr;
        view.viewType = VK_IMAGE_VIEW_TYPE_2D;
        view.format = VK_FORMAT_R8G8B8A8_UNORM;
        view.components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY,
            VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY};
        view.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1};
        vkCreateSampler(LunaLux::vulkanUtilGetDevice(), &sampler, nullptr, &texture.sampler);

        view.image = texture.image;
        vkCreateImageView(LunaLux::vulkanUtilGetDevice(), &view, nullptr, &texture.view);
    }
}

void demo_prepare_cube_data_buffers()
{
    VkMemoryRequirements memoryRequirements;
    VkMemoryAllocateInfo mem_alloc;
    mat4x4 MVP, VP;

    vkTextureCube_vs_uniform data{};

    mat4x4_mul(VP, m_demo.projection_matrix, m_demo.view_matrix);
    mat4x4_mul(MVP, VP, m_demo.model_matrix);
    memcpy(data.mvp, MVP, sizeof(MVP));

    for (unsigned int i = 0; i < 12 * 3; i++)
    {
        data.position[i][0] = g_vertex_buffer_data[i * 3];
        data.position[i][1] = g_vertex_buffer_data[i * 3 + 1];
        data.position[i][2] = g_vertex_buffer_data[i * 3 + 2];
        data.position[i][3] = 1.0f;
        data.attr[i][0] = g_uv_buffer_data[2 * i];
        data.attr[i][1] = g_uv_buffer_data[2 * i + 1];
        data.attr[i][2] = 0;
        data.attr[i][3] = 0;
    }
    VkBufferCreateInfo buf_info = LunaLux::vulkanCreateUniformBufferInfo(0, sizeof(data));

    for (unsigned int i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        vkCreateBuffer(LunaLux::vulkanUtilGetDevice(), &buf_info, nullptr, &m_demo.swapChain_img_res[i].uniform_buffer);

        vkGetBufferMemoryRequirements(LunaLux::vulkanUtilGetDevice(), m_demo.swapChain_img_res[i].uniform_buffer,
                                      &memoryRequirements);

        mem_alloc.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        mem_alloc.pNext = nullptr;
        mem_alloc.allocationSize = memoryRequirements.size;
        mem_alloc.memoryTypeIndex = LunaLux::vulkanFindGpuMemoryType(memoryRequirements.memoryTypeBits,
                                                                     VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
                                                                     VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

        vkAllocateMemory(LunaLux::vulkanUtilGetDevice(), &mem_alloc, nullptr, &m_demo.swapChain_img_res[i].uniform_memory);

        vkMapMemory(LunaLux::vulkanUtilGetDevice(), m_demo.swapChain_img_res[i].uniform_memory, 0, VK_WHOLE_SIZE, 0,
                    &m_demo.swapChain_img_res[i].uniform_memory_ptr);

        memcpy(m_demo.swapChain_img_res[i].uniform_memory_ptr, &data, sizeof data);

        vkBindBufferMemory(LunaLux::vulkanUtilGetDevice(), m_demo.swapChain_img_res[i].uniform_buffer, m_demo.swapChain_img_res[i].uniform_memory, 0);
    }
}

static void demo_prepare_descriptor_layout()
{
    VkDescriptorSetLayoutBinding layout_bindings[2];
    layout_bindings[0].binding = 0;
    layout_bindings[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    layout_bindings[0].descriptorCount = 1;
    layout_bindings[0].stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    layout_bindings[0].pImmutableSamplers = nullptr;
    layout_bindings[1].binding = 1;
    layout_bindings[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    layout_bindings[1].descriptorCount = DEMO_TEXTURE_COUNT;
    layout_bindings[1].stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
    layout_bindings[1].pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo desc_layout = LunaLux::vulkanCreateDescriptorSetLayoutInfo(0);
    desc_layout.bindingCount = 2;
    desc_layout.pBindings = layout_bindings;

    vkCreateDescriptorSetLayout(LunaLux::vulkanUtilGetDevice(), &desc_layout, nullptr, &m_demo.desc_layout);

    VkPipelineLayoutCreateInfo pPipelineLayoutCreateInfo = LunaLux::vulkanCreatePipelineLayoutInfo(0);
    pPipelineLayoutCreateInfo.setLayoutCount = 1;
    pPipelineLayoutCreateInfo.pSetLayouts = &m_demo.desc_layout;
    pPipelineLayoutCreateInfo.pushConstantRangeCount = 0;
    pPipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

    vkCreatePipelineLayout(LunaLux::vulkanUtilGetDevice(), &pPipelineLayoutCreateInfo, nullptr, &m_demo.pipeline_layout);
}

static void demo_prepare_render_pass()
{
    VkAttachmentDescription attachments[2];
    attachments[0].format = LunaLux::vulkanGetSurfaceFormat().format;
    attachments[0].flags = 0;
    attachments[0].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[0].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[0].storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    attachments[0].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[0].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[0].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[0].finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    attachments[1].format = m_demo.depth.format;
    attachments[1].flags = 0;
    attachments[1].samples = VK_SAMPLE_COUNT_1_BIT;
    attachments[1].loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    attachments[1].storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    attachments[1].stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    attachments[1].initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    attachments[1].finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference color_reference = LunaLux::vulkanCreateColourAttRef(0);
    VkAttachmentReference depth_reference = LunaLux::vulkanCreateDepthStencilAttRef(1);

    VkSubpassDescription subPass;
    subPass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subPass.flags = 0;
    subPass.inputAttachmentCount = 0;
    subPass.pInputAttachments = nullptr;
    subPass.colorAttachmentCount = 1;
    subPass.pColorAttachments = &color_reference;
    subPass.pResolveAttachments = nullptr;
    subPass.pDepthStencilAttachment = &depth_reference;
    subPass.preserveAttachmentCount = 0;
    subPass.pPreserveAttachments = nullptr;

    VkSubpassDependency attachmentDependencies[2];
    // Depth buffer is shared between swapChain images
    attachmentDependencies[0].srcSubpass = VK_SUBPASS_EXTERNAL;
    attachmentDependencies[0].dstSubpass = 0;
    attachmentDependencies[0].srcStageMask =
        VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    attachmentDependencies[0].dstStageMask =
        VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT | VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT;
    attachmentDependencies[0].srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    attachmentDependencies[0].dstAccessMask =
        VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    attachmentDependencies[0].dependencyFlags = 0;

    // Image Layout Transition
    attachmentDependencies[1].srcSubpass = VK_SUBPASS_EXTERNAL;
    attachmentDependencies[1].dstSubpass = 0;
    attachmentDependencies[1].srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    attachmentDependencies[1].dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    attachmentDependencies[1].srcAccessMask = 0;
    attachmentDependencies[1].dstAccessMask =
        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT;
    attachmentDependencies[1].dependencyFlags = 0;

    VkRenderPassCreateInfo rp_info = LunaLux::vulkanCreateRenderPassInfo(0);
    rp_info.attachmentCount = 2;
    rp_info.pAttachments = attachments;
    rp_info.subpassCount = 1;
    rp_info.pSubpasses = &subPass;
    rp_info.dependencyCount = 2;
    rp_info.pDependencies = attachmentDependencies;

    vkCreateRenderPass(LunaLux::vulkanUtilGetDevice(), &rp_info, nullptr, &m_demo.render_pass);
}

static VkShaderModule demo_prepare_shader_module(const uint32_t *code, size_t size)
{
    VkShaderModule module;
    VkShaderModuleCreateInfo moduleCreateInfo = LunaLux::vulkanCreateShaderModuleInfo(code, size);
    vkCreateShaderModule(LunaLux::vulkanUtilGetDevice(), &moduleCreateInfo, nullptr, &module);
    return module;
}

static void demo_prepare_pipeline()
{
    VkPipelineVertexInputStateCreateInfo vi = LunaLux::vulkanCreateVertexInputStateInfo(0);

    VkPipelineInputAssemblyStateCreateInfo ia = LunaLux::vulkanCreateInputAssemblyStateInfo(0);
    ia.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;

    VkPipelineRasterizationStateCreateInfo rs = LunaLux::vulkanCreateRasterizationStateInfo(0);
    rs.polygonMode = VK_POLYGON_MODE_FILL;
    rs.cullMode = VK_CULL_MODE_BACK_BIT;
    rs.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rs.depthClampEnable = VK_FALSE;
    rs.rasterizerDiscardEnable = VK_FALSE;
    rs.depthBiasEnable = VK_FALSE;
    rs.lineWidth = 1.0f;

    VkPipelineColorBlendAttachmentState att_state[1]{};
    att_state[0].colorWriteMask = 0xf;
    att_state[0].blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo cb = LunaLux::vulkanCreateColorBlendStateInfo(0);
    cb.attachmentCount = 1;
    cb.pAttachments = att_state;

    VkPipelineDepthStencilStateCreateInfo ds = LunaLux::vulkanCreateDepthStencilStateInfo(0);
    ds.depthTestEnable = VK_TRUE;
    ds.depthWriteEnable = VK_TRUE;
    ds.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
    ds.depthBoundsTestEnable = VK_FALSE;
    ds.back.failOp = VK_STENCIL_OP_KEEP;
    ds.back.passOp = VK_STENCIL_OP_KEEP;
    ds.back.compareOp = VK_COMPARE_OP_ALWAYS;
    ds.stencilTestEnable = VK_FALSE;
    ds.front = ds.back;

    VkDynamicState dynamicStateEnables[2]{};
    VkPipelineDynamicStateCreateInfo dynamicState = LunaLux::vulkanCreateDynamicStateInfo(0);
    dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_VIEWPORT;
    dynamicStateEnables[dynamicState.dynamicStateCount++] = VK_DYNAMIC_STATE_SCISSOR;
    dynamicState.pDynamicStates = dynamicStateEnables;

    VkPipelineViewportStateCreateInfo vp = LunaLux::vulkanCreateViewportStateInfo(0);
    vp.viewportCount = 1;
    vp.scissorCount = 1;

    VkPipelineMultisampleStateCreateInfo ms = LunaLux::vulkanCreateMultisampleStateInfo(0);
    ms.pSampleMask = nullptr;
    ms.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    const uint32_t vs_code[] =
        {
#include "cube.vert.inc"
        };
    m_demo.vert_shader_module = demo_prepare_shader_module(vs_code, sizeof(vs_code));

    const uint32_t fs_code[] =
        {
#include "cube.frag.inc"
        };
    m_demo.frag_shader_module = demo_prepare_shader_module(fs_code, sizeof(fs_code));

    // Two stages: vs and fs
    VkPipelineShaderStageCreateInfo shaderStages[2]{};
    shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[0].pNext = nullptr;
    shaderStages[0].flags = 0;
    shaderStages[0].pName = "main";
    shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
    shaderStages[0].module = m_demo.vert_shader_module;

    shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStages[1].pNext = nullptr;
    shaderStages[1].flags = 0;
    shaderStages[1].pName = "main";
    shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    shaderStages[1].module = m_demo.frag_shader_module;

    VkGraphicsPipelineCreateInfo pipeline = LunaLux::vulkanCreatePipelineInfo(0);
    pipeline.layout = m_demo.pipeline_layout;
    pipeline.pVertexInputState = &vi;
    pipeline.pInputAssemblyState = &ia;
    pipeline.pRasterizationState = &rs;
    pipeline.pColorBlendState = &cb;
    pipeline.pMultisampleState = &ms;
    pipeline.pViewportState = &vp;
    pipeline.pDepthStencilState = &ds;
    pipeline.stageCount = 2;
    pipeline.pStages = shaderStages;
    pipeline.renderPass = m_demo.render_pass;
    pipeline.pDynamicState = &dynamicState;
    pipeline.renderPass = m_demo.render_pass;

    LunaLux::vulkanCreateGraphicsPipeline(&pipeline, &m_demo.pipeline);

    LunaLux::vkDestroyShaderModule(m_demo.frag_shader_module);
    LunaLux::vkDestroyShaderModule(m_demo.vert_shader_module);
}

static void demo_prepare_descriptor_pool()
{
    VkDescriptorPoolSize type_counts[2];
    type_counts[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    type_counts[0].descriptorCount = LunaLux::vulkanGetSwapChainImageCount();
    type_counts[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    type_counts[1].descriptorCount = LunaLux::vulkanGetSwapChainImageCount() * DEMO_TEXTURE_COUNT;

    VkDescriptorPoolCreateInfo descriptor_pool = LunaLux::vulkanCreateDescriptorPoolInfo(0);
    descriptor_pool.maxSets = LunaLux::vulkanGetSwapChainImageCount();
    descriptor_pool.poolSizeCount = 2;
    descriptor_pool.pPoolSizes = type_counts;

    vkCreateDescriptorPool(LunaLux::vulkanUtilGetDevice(), &descriptor_pool, nullptr, &m_demo.desc_pool);
}

static void demo_prepare_descriptor_set()
{
    VkDescriptorImageInfo pDescriptorImageInfo[DEMO_TEXTURE_COUNT];
    VkWriteDescriptorSet writes[2]{};

    VkDescriptorSetAllocateInfo alloc_info = LunaLux::vulkanCreateDescriptorSetAllocateInfo();
    alloc_info.descriptorPool = m_demo.desc_pool;
    alloc_info.descriptorSetCount = 1;
    alloc_info.pSetLayouts = &m_demo.desc_layout;

    VkDescriptorBufferInfo buffer_info;
    buffer_info.offset = 0;
    buffer_info.range = sizeof(struct vkTextureCube_vs_uniform);

    for (unsigned int i = 0; i < DEMO_TEXTURE_COUNT; i++)
    {
        pDescriptorImageInfo[i].sampler = m_demo.textures[i].sampler;
        pDescriptorImageInfo[i].imageView = m_demo.textures[i].view;
        pDescriptorImageInfo[i].imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    }

    writes[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[0].pNext = nullptr;
    writes[0].descriptorCount = 1;
    writes[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    writes[0].pBufferInfo = &buffer_info;

    writes[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    writes[1].pNext = nullptr;
    writes[1].dstBinding = 1;
    writes[1].descriptorCount = DEMO_TEXTURE_COUNT;
    writes[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    writes[1].pImageInfo = pDescriptorImageInfo;

    for (unsigned int i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        vkAllocateDescriptorSets(LunaLux::vulkanUtilGetDevice(), &alloc_info, &m_demo.swapChain_img_res[i].descriptor_set);
        buffer_info.buffer = m_demo.swapChain_img_res[i].uniform_buffer;
        writes[0].dstSet = m_demo.swapChain_img_res[i].descriptor_set;
        writes[1].dstSet = m_demo.swapChain_img_res[i].descriptor_set;
        LunaLux::vkUpdateDescriptorSets(2, writes, 0, nullptr);
    }
}

static void demoPrepareFrameBuffers()
{
    VkImageView attachments[2];
    attachments[1] = m_demo.depth.view;

    VkFramebufferCreateInfo fb_info = LunaLux::vulkanCreateFramebufferInfo(0);
    fb_info.renderPass = m_demo.render_pass;
    fb_info.attachmentCount = 2;
    fb_info.pAttachments = attachments;
    fb_info.width = static_cast<uint32_t>(std::get<0>(LunaLux::GetWindowSize()));
    fb_info.height = static_cast<uint32_t>(std::get<1>(LunaLux::GetWindowSize()));
    fb_info.layers = 1;

    for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        attachments[0] = LunaLux::vulkanGetSwapChainImageViews()[i];
        vkCreateFramebuffer(LunaLux::vulkanUtilGetDevice(), &fb_info, nullptr, &m_demo.swapChain_img_res[i].frameBuffer);
    }
}

static void demo_prepare()
{
    if (m_demo.cmd_pool == nullptr)
    {
        VkCommandPoolCreateInfo cmd_pool_info = LunaLux::vulkanCreateCommandPoolCreateInfo(0);
        cmd_pool_info.queueFamilyIndex = LunaLux::vulkanGetGraphicsFamilyIndex();
        LunaLux::vkCreateCommandPool(&cmd_pool_info, &m_demo.cmd_pool);
    }

    VkCommandBufferAllocateInfo cmd = LunaLux::vulkanCreateCommandBufferAllocateInfo();
    cmd.commandPool = m_demo.cmd_pool;
    cmd.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    cmd.commandBufferCount = 1;

    vkAllocateCommandBuffers(LunaLux::vulkanUtilGetDevice(), &cmd, &m_demo.cmd);

    VkCommandBufferBeginInfo cmd_buf_info = LunaLux::vulkanCreateCommandBufferBeginInfo(0);
    cmd_buf_info.pInheritanceInfo = nullptr;

    vkBeginCommandBuffer(m_demo.cmd, &cmd_buf_info);

    demo_prepare_buffers();

    if (m_demo.is_minimized)
    {
        m_demo.prepared = false;
        return;
    }

    demo_prepare_depth();
    demo_prepare_textures();
    demo_prepare_cube_data_buffers();
    demo_prepare_descriptor_layout();
    demo_prepare_render_pass();
    demo_prepare_pipeline();

    for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        vkAllocateCommandBuffers(LunaLux::vulkanUtilGetDevice(), &cmd, &m_demo.swapChain_img_res[i].cmd);
    }

    if (m_demo.separate_present_queue)
    {
        VkCommandPoolCreateInfo present_cmd_pool_info = LunaLux::vulkanCreateCommandPoolCreateInfo(0);
        present_cmd_pool_info.queueFamilyIndex = LunaLux::vulkanGetPresentFamilyIndex();

        vkCreateCommandPool(LunaLux::vulkanUtilGetDevice(), &present_cmd_pool_info, nullptr, &m_demo.present_cmd_pool);

        VkCommandBufferAllocateInfo present_cmd_info = LunaLux::vulkanCreateCommandBufferAllocateInfo();
        present_cmd_info.commandPool = m_demo.present_cmd_pool;
        present_cmd_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        present_cmd_info.commandBufferCount = 1;

        for (int32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
        {
            vkAllocateCommandBuffers(LunaLux::vulkanUtilGetDevice(), &present_cmd_info, &m_demo.swapChain_img_res[i].graphics_to_present_cmd);
            demo_build_image_ownership_cmd(i);
        }
    }

    demo_prepare_descriptor_pool();
    demo_prepare_descriptor_set();

    demoPrepareFrameBuffers();

    for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        m_demo.current_buffer = i;
        demo_draw_build_cmd(m_demo.swapChain_img_res[i].cmd);
    }

    demo_flush_init_cmd();
    if (m_demo.staging_texture.buffer)
    {
        demo_destroy_texture(&m_demo.staging_texture);
    }

    m_demo.current_buffer = 0;
    m_demo.prepared = true;
}

static void demo_cleanup()
{
    m_demo.prepared = false;
    LunaLux::vkDeviceWaitIdle();

    for (uint32_t i = 0; i < FRAME_LAG; i++)
    {
        LunaLux::vkWaitForFences(1, &m_demo.fences[i], VK_TRUE, UINT64_MAX);
        LunaLux::vkDestroyFence(m_demo.fences[i]);
        LunaLux::vkDestroySemaphore(m_demo.image_acquired_semaphores[i]);
        LunaLux::vkDestroySemaphore(m_demo.draw_complete_semaphores[i]);
        if (m_demo.separate_present_queue)
        {
            LunaLux::vkDestroySemaphore(m_demo.image_ownership_semaphores[i]);
        }
    }

    if (!m_demo.is_minimized)
    {
        for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
        {
            LunaLux::vkDestroyFramebuffer(m_demo.swapChain_img_res[i].frameBuffer);
        }
        LunaLux::vkDestroyDescriptorPool(m_demo.desc_pool);
        LunaLux::vulkanDestroyGraphicsPipeline(&m_demo.pipeline);
        LunaLux::vkDestroyRenderPass(m_demo.render_pass);
        LunaLux::vkDestroyPipelineLayout(m_demo.pipeline_layout);
        LunaLux::vkDestroyDescriptorSetLayout(m_demo.desc_layout);

        for (auto &texture : m_demo.textures)
        {
            LunaLux::vkDestroyImageView(texture.view);
            LunaLux::vkDestroyImage(texture.image);
            LunaLux::vkFreeMemory(texture.mem);
            LunaLux::vkDestroySampler(texture.sampler);
        }

        LunaLux::vkDestroyImageView(m_demo.depth.view);
        LunaLux::vkDestroyImage(m_demo.depth.image);
        LunaLux::vkFreeMemory(m_demo.depth.mem);

        for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
        {
            LunaLux::vkFreeCommandBuffers(m_demo.cmd_pool, 1, &m_demo.swapChain_img_res[i].cmd);
            LunaLux::vkDestroyBuffer(m_demo.swapChain_img_res[i].uniform_buffer);
            LunaLux::vkUnmapMemory(m_demo.swapChain_img_res[i].uniform_memory);
            LunaLux::vkFreeMemory(m_demo.swapChain_img_res[i].uniform_memory);
        }
        free(m_demo.swapChain_img_res);
        LunaLux::vkDestroyCommandPool(m_demo.cmd_pool);

        if (m_demo.separate_present_queue)
        {
            LunaLux::vkDestroyCommandPool(m_demo.present_cmd_pool);
        }
    }
    LunaLux::vkDeviceWaitIdle();
    LunaLux::vulkanCleanUp();
    LunaLux::closeWindow();
}

static void demo_resize()
{
    if (!m_demo.prepared)
    {
        if (m_demo.is_minimized)
        {
            demo_prepare();
        }
        return;
    }
    m_demo.prepared = false;
    LunaLux::vkDeviceWaitIdle();

    for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        LunaLux::vkDestroyFramebuffer(m_demo.swapChain_img_res[i].frameBuffer);
    }
    LunaLux::vkDestroyDescriptorPool(m_demo.desc_pool);
    LunaLux::vulkanDestroyGraphicsPipeline(&m_demo.pipeline);
    LunaLux::vkDestroyRenderPass(m_demo.render_pass);
    LunaLux::vkDestroyPipelineLayout(m_demo.pipeline_layout);
    LunaLux::vkDestroyDescriptorSetLayout(m_demo.desc_layout);

    for (auto &texture : m_demo.textures)
    {
        LunaLux::vkDestroyImageView(texture.view);
        LunaLux::vkDestroyImage(texture.image);
        LunaLux::vkFreeMemory(texture.mem);
        LunaLux::vkDestroySampler(texture.sampler);
    }
    LunaLux::vkDestroyImageView(m_demo.depth.view);
    LunaLux::vkDestroyImage(m_demo.depth.image);
    LunaLux::vkFreeMemory(m_demo.depth.mem);

    for (uint32_t i = 0; i < LunaLux::vulkanGetSwapChainImageCount(); i++)
    {
        LunaLux::vkFreeCommandBuffers(m_demo.cmd_pool, 1, &m_demo.swapChain_img_res[i].cmd);
        LunaLux::vkDestroyBuffer(m_demo.swapChain_img_res[i].uniform_buffer);
        LunaLux::vkUnmapMemory(m_demo.swapChain_img_res[i].uniform_memory);
        LunaLux::vkFreeMemory(m_demo.swapChain_img_res[i].uniform_memory);
    }
    LunaLux::vkDestroyCommandPool(m_demo.cmd_pool);
    m_demo.cmd_pool = nullptr;
    if (m_demo.separate_present_queue)
    {
        LunaLux::vkDestroyCommandPool(m_demo.present_cmd_pool);
    }
    free(m_demo.swapChain_img_res);

    LunaLux::vulkanResizeSwapChain(LunaLux::GetWindowSize());
    demo_prepare();
}

int main()
{
    LunaLux::createWindow("Vulkan Cube", 500, 500);
    vec3 eye = {0.0f, 3.0f, 5.0f};
    vec3 origin = {0, 0, 0};
    vec3 up = {0.0f, 1.0f, 0.0};
    m_demo.frameCount = INT32_MAX;
    m_demo.spin_angle = 4.0f;
    LunaLux::vulkanInit(LunaLux::getNativeWindow(), {500, 500});

    mat4x4_perspective(m_demo.projection_matrix, (float)degreesToRadians(45.0f), 1.0f, 0.1f, 100.0f);
    mat4x4_look_at(m_demo.view_matrix, eye, origin, up);
    mat4x4_identity(m_demo.model_matrix);
    m_demo.projection_matrix[1][1] *= -1; // Flip projection matrix from GL to Vulkan orientation.
    m_demo.separate_present_queue = (LunaLux::vulkanGetGraphicsFamilyIndex() != LunaLux::vulkanGetPresentFamilyIndex());
    m_demo.curFrame = 0;

    VkSemaphoreCreateInfo semaphoreInfo = LunaLux::vulkanCreateSemaphoreInfo(0);
    VkFenceCreateInfo fence_ci = LunaLux::vulkanCreateFenceInfo(VK_FENCE_CREATE_SIGNALED_BIT);

    for (uint32_t i = 0; i < FRAME_LAG; i++)
    {
        LunaLux::vkCreateFence(&fence_ci, &m_demo.fences[i]);
        LunaLux::vkCreateSemaphore(&semaphoreInfo, &m_demo.image_acquired_semaphores[i]);
        LunaLux::vkCreateSemaphore(&semaphoreInfo, &m_demo.draw_complete_semaphores[i]);
        if (m_demo.separate_present_queue)
        {
            LunaLux::vkCreateSemaphore(&semaphoreInfo, &m_demo.image_ownership_semaphores[i]);
        }
    }
    m_demo.frame_index = 0;
    demo_prepare();

    while (!LunaLux::shouldCloseWindow())
    {
        LunaLux::updateWindow();
        if (LunaLux::HasWindowResized())
        {
            demo_resize();
        }
        if (m_demo.prepared)
        {
            demo_draw();
            m_demo.curFrame++;
            if (m_demo.frameCount != INT32_MAX && m_demo.curFrame == m_demo.frameCount)
            {
                PostQuitMessage(0);
            }
        }
    }
    demo_cleanup();
    return 0;
}