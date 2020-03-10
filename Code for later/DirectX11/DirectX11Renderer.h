//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_DIRECTX_H
#define LUNALUXENGINE_DIRECTX_H
#include <LLESDK/types.h>
#include "../Renderer.h"
#include "../../render/Common/IRender.h"
#ifdef UWP
#include <D3D11.h>
#pragma comment ( lib, "D3d11.lib" )

namespace LunaLuxEngine
{
	class DXRenderer : public IRender
	{
	private:
		IDXGISwapChain* swapchain{};             // the pointer to the swap chain interface
	public:
		void prepRender() override {};
		void initRender() override;
		void postRender() override {};
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif
#endif //LUNALUXENGINE_DIRECTX_H
