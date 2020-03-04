#ifndef LUNALUXENGINE_IRENDER_H
#define LUNALUXENGINE_IRENDER_H
#include "../../window/Window.h"
#include "GPUInstance.h"
namespace LunaLuxEngine
{
	class IRender
	{
	protected:
		GPUInstance* inst{};
	public:
		virtual void initRender(GPUInstance* inst_in) {};

		virtual void prepRender() {};

		virtual void fireRender() {};

		virtual void postRender() {};

		virtual void destroyRender() {};
	};
}
#endif