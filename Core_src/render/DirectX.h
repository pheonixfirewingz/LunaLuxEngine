//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_DIRECTX_H
#define LUNALUXENGINE_DIRECTX_H
#ifdef WIN32
#pragma comment ( lib, "D3d11.lib" )
#include <D3D11.h>
IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
ID3D11Device *dev;                     // the pointer to our Direct3D device interface
ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
ID3D11InputLayout *pLayout;            // the pointer to the input layout
ID3D11VertexShader *pVS;               // the pointer to the vertex shader
ID3D11PixelShader *pPS;                // the pointer to the pixel shader
ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
#endif
#endif //LUNALUXENGINE_DIRECTX_H
