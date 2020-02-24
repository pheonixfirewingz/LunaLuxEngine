//
// Created by luket on 23/01/2020.
//
#include "../Common/IRender.h"
#ifdef WIN32
#include "DirectX.h"
#include "../Shader.h"
#include "../Buffer.h"
#include "../../utils/BufferUtil.h"
using namespace LunaLuxEngine;
int32 r_width, r_height;

inline void WindowResizeCallback(int32 width, int32 height)
{
	r_width = width; //takes game window current width and sets the internal renderer width
	r_height = height; //takes game window current height and sets the internal renderer height
}
void DXRenderer::initRender(window_api::CrossWindow* win)
{
	CWin->setResizeCallback(&WindowResizeCallback);
	CWin->fireResizeCallback(CWin->getWindowW(), CWin->getWindowH());
	/*
	  * =====================================================
	  * 				 GRAPHICS SETUP INSTANCE
	  * =====================================================
	  */
	  // create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC scd;
	// clear out the struct for use
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));
	// fill the swap chain description struct
	scd.BufferCount = 1;                                    // one back buffer
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
	scd.BufferDesc.Width = win->getWindowW();                    // set the back buffer width
	scd.BufferDesc.Height = win->getWindowH();                  // set the back buffer height
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
	scd.OutputWindow = win->getWindow();                                // the window to be used
	scd.SampleDesc.Count = 1;                               // how many multisamples
	scd.SampleDesc.Quality = 0;                             // multisample quality level
	scd.Windowed = true;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching
	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		NULL, nullptr, NULL, D3D11_SDK_VERSION, &scd, &swapchain, &dev, nullptr, &devcon);
	// get the address of the back buffer
	ID3D11Texture2D* pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, nullptr, &backbuffer);
	pBackBuffer->Release();

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = CWin->getWindowW();
	depthStencilDesc.Height = CWin->getWindowH();
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	dev->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
	dev->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, depthStencilView);
	/*
	  * =====================================================
	  * 				 GRAPHICS SETUP INSTANCE END
	  * =====================================================
	  *
	  *=======================================================
	  *					SET UP RENDER DATA
	  *=======================================================
	  */
	BufferUtils::get()->giveInstance(dev);
	Shaders::get()->giveInstance(dev, devcon);
	//temp
	Shaders::get()->compileShader(L"shader.hlsl");
	/*
	  *=======================================================
	  *					END SET UP RENDER DATA
	  *=======================================================
	  */
}

void DXRenderer::prepRender()
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = r_width;
	viewport.Height = r_height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	devcon->RSSetViewports(1, &viewport);
}

float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
UINT offset = 0;
void DXRenderer::fireRender()
{
	devcon->ClearRenderTargetView(backbuffer, color);
	devcon->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	devcon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	for (int i = 0; i < BufferUtils::get()->getBufferCount(); i++)
	{
		//TODO: need to get the current vertex count from the current vertex buffer beening drawn to make this dynamtic
		UINT stride = 4;
		devcon->IASetVertexBuffers(0, 1, BufferUtils::get()->getVbuff(i), &stride, &offset);
		devcon->IASetIndexBuffer(BufferUtils::get()->getIBuff(i), DXGI_FORMAT_R32_UINT, offset);
		//TODO: need to get the current indices count from the current indices buffer beening drawn to make this dynamtic
		devcon->DrawIndexed(BufferUtils::get()->getGlobalIndicesCount(), 0, 0);
	}
	swapchain->Present(0, 0);
}

void DXRenderer::postRender()
{

}

void DXRenderer::destroyRender()
{
	/*TODO: there nullptrs idk wky?
	 *depthStencilView->Release();
	 *depthStencilBuffer->Release();
	 */
	swapchain->SetFullscreenState(FALSE, NULL);
	Shaders::get()->clearShaders();
	BufferUtils::get()->releaseBuffers();
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
#endif