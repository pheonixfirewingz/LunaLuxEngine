//
// Created by luket on 23/01/2020.
//
#include "DirectX11Renderer.h"
#ifdef UWP
#include "../Renderer.h"
#include "../../oldrender/Buffer.h"
using namespace LunaLuxEngine;

inline void WindowResizeCallback(int32 width, int32 height)
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
	Renderer::get()->getInst()->getGPUDeviceContext()->dx11_deviceContext->RSSetViewports(1, &viewport);
}

void DXRenderer::initRender(GPUInstance* inst_in)
{
	inst = inst_in;
	CWin->setResizeCallback(&WindowResizeCallback);
	swapchain = inst_in->createDX11GPUInstance();
	CWin->fireResizeCallback(CWin->getWindowW(), CWin->getWindowH());
}


UINT offset = 0, stride = 4;
void DXRenderer::fireRender()
{
	inst->getGPUDeviceContext()->dx11_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//TODO: need to get the current vertex count from the current vertex buffer beening drawn to make this dynamtic
	inst->getGPUDeviceContext()->dx11_deviceContext->IASetVertexBuffers(0, 1, BufferUtils::get()->getVbuff(0), &stride, &offset);
	inst->getGPUDeviceContext()->dx11_deviceContext->IASetIndexBuffer(BufferUtils::get()->getIBuff(0), DXGI_FORMAT_R32_UINT, 0);
	//TODO: need to get the current indices count from the current indices buffer beening drawn to make this dynamtic
	inst->getGPUDeviceContext()->dx11_deviceContext->DrawIndexed(BufferUtils::get()->getGlobalIndicesCount(), 0, 0);
	swapchain->Present(0, 0);
}

void DXRenderer::destroyRender()
{
	swapchain->SetFullscreenState(FALSE, NULL);
	swapchain->Release();
}
#endif