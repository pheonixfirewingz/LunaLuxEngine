#ifndef LUNALUXENGINE_GPUINSTANCE_H
#define LUNALUXENGINE_GPUINSTANCE_H
#include <LLESDK/types.h>
#include "../../window/Window.h"
#ifdef UWP
#include <d3d11.h>
#endif
#include <vulkan/vulkan.h>

namespace LunaLuxEngine
{
	class GPUInstance
	{
	private:
		struct GPUDEVICECONTEXT
		{
#ifdef UWP
			ID3D11DeviceContext* dx11_deviceContext;
#endif
			VkPhysicalDevice* vk_deviceContext;
		};

		struct GPUDEVICE
		{
#ifdef UWP
			ID3D11Device* dx11_device;
#endif
			VkInstance vk_instance;
			VkDevice* vk_device;

			void Dx11Release(GPUDEVICECONTEXT* context);
		};
		GPUDEVICE* device = new GPUDEVICE();
		GPUDEVICECONTEXT* deviceContext = new GPUDEVICECONTEXT();
#ifdef UWP
		ID3D11RenderTargetView* backbuffer{};    // the pointer to our back buffer
		ID3D11DepthStencilView* depthStencilView{};

		void dx11Clenup();
		void dx11ClearScreen(float color[4]);
	public:
		IDXGISwapChain* createDX11GPUInstance();
#else
		void dx11Clenup() {}
		void dx11ClearScreen(float color[4]) {}
#endif
	public:
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
			if (device->dx11_device != nullptr)
				dx11ClearScreen(colour);
		}
	};
}
#endif