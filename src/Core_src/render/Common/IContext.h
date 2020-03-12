#ifndef LUNALUXENGINE_CONTEXT_H
#define LUNALUXENGINE_CONTEXT_H
#include "../../window/Window.h"
namespace LunaLuxEngine
{
	class IContext
	{
	public:
		virtual void create() = 0;
		virtual void swapBuffers() = 0;
		virtual void destroy() = 0;
	};
}
#endif