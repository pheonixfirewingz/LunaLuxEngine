//
// Created by luket on 23/01/2020.
//
#include "IRender.h"
#ifdef WIN32
#ifdef MSVC

#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/dxgi.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d11.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d10.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d10_1.lib" )
#pragma comment ( lib, "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/libs/x64/d3d9.lib" )
#endif
#include <d3d11.h>
#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning
#include <strsafe.h>
#pragma warning( default : 4996 )
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // the rendering device
LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold vertices

void IRender::initRender(HWND hwnd)
{
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		std::exit(-10);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&d3dpp, &g_pd3dDevice)))
		std::exit(-10);
}

void IRender::destroyRender()
{

}

void IRender::fireRender()
{

}

void IRender::prepRender()
{

}
#endif