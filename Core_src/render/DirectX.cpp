//
// Created by luket on 23/01/2020.
//
#include "IRender.h"
#ifdef WIN32
#include "DirectX.h"
using namespace LunaLuxEngine;
struct COLOUR
{
	FLOAT  r;
	FLOAT  g;
	FLOAT  b;
	FLOAT  a;
	COLOUR(float d, float d1, float d2, float d3)
	{
		this->r = d;
		this->g = d1;
		this->b = d2;
		this->a = d3;
	}
};
struct VERTEX
{
	float x, y, z;
	COLOUR color;
};

VERTEX OurVertices[] =
		{
				{0.0f, 0.5f, 0.0f, COLOUR(1.0f, 0.0f, 0.0f, 1.0f)},
				{0.45f, -0.5, 0.0f, COLOUR(0.0f, 1.0f, 0.0f, 1.0f)},
				{-0.45f, -0.5f, 0.0f, COLOUR(0.0f, 0.0f, 1.0f, 1.0f)}
		};

void IRender::initRender(window_api::CrossWindow* win)
{
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
	scd.Windowed = TRUE;                                    // windowed/full-screen mode
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching


	// create a device, device context and swap chain using the information in the scd struct
	D3D11CreateDeviceAndSwapChain(NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&scd,
			&swapchain,
			&dev,
			NULL,
			&devcon);


	// get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	// use the back buffer address to create the render target
	dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
	pBackBuffer->Release();

	// set the render target as the back buffer
	devcon->OMSetRenderTargets(1, &backbuffer, NULL);


	// Set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = win->getWindowW();
	viewport.Height = win->getWindowH();

	devcon->RSSetViewports(1, &viewport);


	/*
	 * =====================================================
	 * 				 GRAPHICS INIT END
	 * =====================================================
	 */


	// create the vertex buffer
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
	bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

	dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer


	// copy the vertices into the buffer
	D3D11_MAPPED_SUBRESOURCE ms;
	devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
	memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
	devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer

	// load and compile the two shaders
	ID3D10Blob *VS, *PS;

	/*TODO: need setting up uninitialized local variables
	 * Core_src\render\DirectX.cpp(125) : warning C4700: uninitialized local variable 'VS' used
	 * Core_src\render\DirectX.cpp(126) : warning C4700: uninitialized local variable 'PS' used
	 */

	// encapsulate both shaders into shader objects
	dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	// set the shader objects
	devcon->VSSetShader(pVS, 0, 0);
	devcon->PSSetShader(pPS, 0, 0);

	// create the input layout object
	D3D11_INPUT_ELEMENT_DESC ied[] =
			{
					{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
					{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

	dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	devcon->IASetInputLayout(pLayout);
}

void IRender::destroyRender()
{
	// close and release all existing COM objects
	pLayout->Release();
	pVS->Release();
	pPS->Release();
	pVBuffer->Release();
	swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode
	swapchain->Release();
	backbuffer->Release();
	dev->Release();
	devcon->Release();
}
float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
void IRender::fireRender()
{
	// clear the back buffer to a deep blue
	devcon->ClearRenderTargetView(backbuffer, color);

	// do 3D rendering on the back buffer here

	// select which vertex buffer to display
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

	// select which primtive type we are using
	devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// draw the vertex buffer to the back buffer
	devcon->Draw(3, 0);

	// switch the back buffer and the front buffer
	swapchain->Present(0, 0);
}

void IRender::prepRender()
{

}
#endif