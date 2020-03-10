#ifndef LUNALUXENGINE_GPUINSTANCE_H
#define LUNALUXENGINE_GPUINSTANCE_H
#include <LLESDK/types.h>
#include "../../window/Window.h" 
#ifdef UWP
#pragma comment(lib,"opengl32.lib")
#endif
#include <vulkan/vulkan.h>
#include <glad\glad.h>

namespace LunaLuxEngine
{
	class GPUInstance
	{
	private:
		GPUInstance() {};
		~GPUInstance() {};
	public:
		static GPUInstance& getInstance()
		{
			static GPUInstance inst;
			return inst;
		}
		GPUInstance(GPUInstance const&) = delete;
		void operator=(GPUInstance const&) = delete;
	private:
		struct GPUDEVICECONTEXT
		{
			VkPhysicalDevice* vk_deviceContext;
		};

		struct GPUDEVICE
		{
#ifdef UWP
			HDC dc;
			HGLRC rc;
#endif
			VkInstance vk_instance;
			VkDevice* vk_device;
		};
		GPUDEVICE* device = new GPUDEVICE();
		GPUDEVICECONTEXT* deviceContext = new GPUDEVICECONTEXT();

	public:
		void createOGLGPUInstance();
		inline GPUDEVICE* getGPUDevice()
		{
			return device;
		}

		inline GPUDEVICECONTEXT* getGPUDeviceContext()
		{
			return deviceContext;
		}

		void Release();

		inline void cleanScreen(float colour[4])
		{
			glClearColor(colour[0], colour[1], colour[2], colour[3]);
			glClear(GL_COLOR_BUFFER_BIT);
		}
	};
}
#endif