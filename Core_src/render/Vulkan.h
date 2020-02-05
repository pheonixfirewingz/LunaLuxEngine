//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_VULKAN_H
#define LUNALUXENGINE_VULKAN_H

#include "IRender.h"
#include <vulkan/vulkan.h>
#include "../window/Window.h"
#include <vector>
#ifdef WIN32
#include <windows.h>
#endif

namespace LunaLuxEngine
{
	class VKRenderer : public IRender
    {
    private:
	    VkInstance instance = nullptr;
	    VkSurfaceKHR surface = nullptr;
	    VkPhysicalDevice pDevice = nullptr;
	    VkDevice device = nullptr;
	    VkSwapchainKHR swapChain = nullptr;
	    VkImage* image = nullptr;
	    VkImageView image_v = nullptr;
	    VkRenderPass renderPass = nullptr;
	    VkFramebuffer* framebuffer = nullptr;
	    VkCommandBuffer commandBuffer = nullptr;
	    VkBuffer vertexInputBuffer = nullptr;
	    VkPipeline pipeline = nullptr;
	    VkPipelineLayout pipelineLayout = nullptr;
	    const char *extentions[3] = {"VK_KHR_surface","VK_KHR_win32_surface","VK_EXT_debug_report"};
    public:
		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif //LUNALUXENGINE_VULKAN_H
