//
// Created by luket on 23/01/2020.
//
#include "DirectX11Renderer.h"
#ifdef UWP
#include "../../oldrender/Buffer.h"
using namespace LunaLuxEngine;

inline void DXWindowResizeCallback(int32 width, int32 height)
{
	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;
	viewport.Height = height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	Renderer::get()->instance.getGPUDeviceContext()->dx11_deviceContext->RSSetViewports(1, &viewport);
}

void DXRenderer::initRender()
{
	CWin.setResizeCallback(&DXWindowResizeCallback);
	swapchain = Renderer::get()->instance.createDX11GPUInstance();

}


UINT offset = 0, stride = 4;
void DXRenderer::fireRender()
{
	Renderer::get()->instance.getGPUDeviceContext()->dx11_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//TODO: need to get the current vertex count from the current vertex buffer beening drawn to make this dynamtic
	Renderer::get()->instance.getGPUDeviceContext()->dx11_deviceContext->IASetVertexBuffers(0, 1, BufferUtils::get()->getVbuff(0), &stride, &offset);
	Renderer::get()->instance.getGPUDeviceContext()->dx11_deviceContext->IASetIndexBuffer(BufferUtils::get()->getIBuff(0), DXGI_FORMAT_R32_UINT, 0);
	//TODO: need to get the current indices count from the current indices buffer beening drawn to make this dynamtic
	Renderer::get()->instance.getGPUDeviceContext()->dx11_deviceContext->DrawIndexed(BufferUtils::get()->getGlobalIndicesCount(), 0, 0);
	swapchain->Present(0, 0);
}

void DXRenderer::destroyRender()
{
	swapchain->SetFullscreenState(FALSE, NULL);
	swapchain->Release();
	swapchain = nullptr;
}
#endif