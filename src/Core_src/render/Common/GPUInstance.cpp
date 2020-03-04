#include "GPUInstance.h"

namespace LunaLuxEngine
{
	void GPUInstance::Release()
	{
		device->Dx11Release(deviceContext);
		if (device->vk_device != nullptr) vkDestroyDevice(*device->vk_device, nullptr);
		if (device->vk_instance != nullptr) vkDestroyInstance(device->vk_instance, nullptr);
		dx11Clenup();
	}
#ifdef UWP
	void GPUInstance::GPUDEVICE::Dx11Release(GPUDEVICECONTEXT* context)
	{
		if (dx11_device != nullptr) dx11_device->Release();
		if (context->dx11_deviceContext != nullptr) context->dx11_deviceContext->Release();
	};

	void GPUInstance::dx11Clenup()
	{
		if (backbuffer != nullptr) backbuffer->Release();
		if (depthStencilView != nullptr) depthStencilView->Release();
	}
	void GPUInstance::dx11ClearScreen(float color[4])
	{
		deviceContext->dx11_deviceContext->ClearRenderTargetView(backbuffer, color);
		deviceContext->dx11_deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	IDXGISwapChain* GPUInstance::createDX11GPUInstance()
	{
		IDXGISwapChain* swapchain;
		// create a struct to hold information about the swap chain
		DXGI_SWAP_CHAIN_DESC scd;
		// clear out the struct for use
		ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
		// fill the swap chain description struct
		scd.BufferCount = 1;                                    // one back buffer
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
		scd.BufferDesc.Width = CWin->getWindowW();                    // set the back buffer width
		scd.BufferDesc.Height = CWin->getWindowH();                  // set the back buffer height
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
		scd.OutputWindow = CWin->getWindow();                                // the window to be used
		scd.SampleDesc.Count = 1;                               // how many multisamples
		scd.SampleDesc.Quality = 0;                             // multisample quality level
		scd.Windowed = true;                                    // windowed/full-screen mode
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching
		// create a device, device context and swap chain using the information in the scd struct
		D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			NULL, nullptr, NULL, D3D11_SDK_VERSION, &scd, &swapchain, &device->dx11_device, nullptr, &deviceContext->dx11_deviceContext);

		// get the address of the back buffer
		ID3D11Texture2D* pBackBuffer;
		swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		// use the back buffer address to create the render target
		device->dx11_device->CreateRenderTargetView(pBackBuffer, nullptr, &backbuffer);
		pBackBuffer->Release();

		D3D11_TEXTURE2D_DESC descDepth = {};
		descDepth.Width = CWin->getWindowW();
		descDepth.Height = CWin->getWindowH();
		descDepth.MipLevels = 1u;
		descDepth.ArraySize = 1u;
		descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		descDepth.SampleDesc.Count = 1u;
		descDepth.SampleDesc.Quality = 0u;
		descDepth.Usage = D3D11_USAGE_DEFAULT;
		descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		ID3D11Texture2D* depthStencilBuffer{};
		device->dx11_device->CreateTexture2D(&descDepth, NULL, &depthStencilBuffer);
		device->dx11_device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
		depthStencilBuffer->Release();
		deviceContext->dx11_deviceContext->OMSetRenderTargets(1, &backbuffer, depthStencilView);
		return swapchain;
	}
#endif
};