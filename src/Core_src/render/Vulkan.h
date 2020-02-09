//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_VULKAN_H
#define LUNALUXENGINE_VULKAN_H

#include "IRender.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "../window/Window.h"
#include <windows.h>

#define VK_KHR_PLATFOM_SUFRACE  "VK_KHR_win32_surface" 

namespace LunaLuxEngine
{
	class VKRenderer : public IRender
    {
    private:
#define CHECK(result) \
if(result != VK_SUCCESS) exit(EXIT_FAILURE);
#define CHECK_B(result) \
if(result != true) exit(EXIT_FAILURE);
#define CHECK_P(result) \
if(result == nullptr) exit(EXIT_FAILURE);

	    VkInstance instance = nullptr;
	    VkSurfaceKHR surface = nullptr;
	    VkPhysicalDevice pDevice = nullptr;
	    VkDevice device = nullptr;
	    VkSwapchainKHR swapChain = nullptr;
	    VkImage* image = nullptr;
	    VkImageView* image_v = nullptr;
	    VkRenderPass renderPass = nullptr;
	    VkFramebuffer* framebuffer = nullptr;
	    VkCommandBuffer commandBuffer = nullptr;
	    VkBuffer vertexInputBuffer = nullptr;
	    VkPipeline pipeline = nullptr;
	    VkPipelineLayout pipelineLayout = nullptr;
	    VkDebugReportCallbackEXT debug_ext = nullptr;
    public:
		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif //LUNALUXENGINE_VULKAN_H