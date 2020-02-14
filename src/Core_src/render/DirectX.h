//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_DIRECTX_H
#define LUNALUXENGINE_DIRECTX_H
#ifdef WIN32
#include <D3D11.h>
#pragma comment ( lib, "D3d11.lib" )
#include "IRender.h"

namespace LunaLuxEngine
{
	class DXRenderer : public IRender
	{
	private:
		IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
		ID3D11Device* dev;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
		ID3D11RenderTargetView* backbuffer;    // the pointer to our back buffer
	public:
		void initRender(window_api::CrossWindow*) override;
		void prepRender() override;
		void fireRender() override;
		void postRender() override;
		void destroyRender() override;
	};
}
#endif
#endif //LUNALUXENGINE_DIRECTX_H
