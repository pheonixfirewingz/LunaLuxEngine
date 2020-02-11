//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_VULKAN_H
#define LUNALUXENGINE_VULKAN_H

#include "IRender.h"
#include <vulkan/vulkan.h>
#include <vulkan/vulkan_win32.h>
#include "../window/Window.h"
#include	"../fs/Reader.h"
#include <windows.h>
#include <vector>
#include <fstream>

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
		/*
		 * ===============================================
		 * 				Context Variables
		 * ===============================================
		 *
		 */
	    VkInstance instance = nullptr;
	    VkSurfaceKHR surface = nullptr;
	    VkPhysicalDevice pDevice = nullptr;
	    VkDevice device = nullptr;
	    VkSwapchainKHR swapChain = nullptr;
	    VkImage* image = nullptr;
	    VkImageView* image_v = nullptr;
	    VkDebugReportCallbackEXT debug_ext = nullptr;
		VkShaderModule vertShaderModule = nullptr;
		VkShaderModule fragShaderModule = nullptr;
		VkRenderPass renderPass = nullptr;
		VkPipeline pipeline = nullptr;
		VkPipelineLayout pipelineLayout = nullptr;
		/*
		 * ===============================================
		 * 			End Of Context Variables
		 * ===============================================
		 *
		 */
		VkFramebuffer* framebuffer = nullptr;
		VkCommandBuffer* commandBuffers = nullptr;
		VkSemaphore imageAvailableSemaphore = nullptr;
		VkSemaphore renderFinishedSemaphore = nullptr;

	private:
		
		inline VkShaderModule createShaderModule(const std::vector<char>& code) 
		{
			VkResult res;
			memset(&res, 0, 0);
			VkShaderModuleCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			createInfo.codeSize = code.size();
			createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

			VkShaderModule shaderModule;
			res = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
			
			CHECK(res);

			return shaderModule;
		}
    public:
		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void postRender() override;
		void destroyRender() override;
	};
}
#endif 