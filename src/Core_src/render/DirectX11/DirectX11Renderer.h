//
// Created by luket on 04/02/2020.
//

#ifndef LUNALUXENGINE_DIRECTX_H
#define LUNALUXENGINE_DIRECTX_H
#ifdef WIN32
#include <D3D11.h>
#pragma comment ( lib, "D3d11.lib" )
#include "../../render/Common/IRender.h"

namespace LunaLuxEngine
{
	class DXRenderer : public IRender
	{
	private:
		IDXGISwapChain* swapchain{};             // the pointer to the swap chain interface
	public:
		void initRender(GPUInstance* inst_in) override;
		void fireRender() override;
		void destroyRender() override;
	};
}
#endif
#endif //LUNALUXENGINE_DIRECTX_H
