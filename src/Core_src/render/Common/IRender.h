#ifndef LUNALUXENGINE_IRENDER_H
#define LUNALUXENGINE_IRENDER_H
#include <LLESDK/types.h>
namespace LunaLuxEngine
{
	class IRender
	{
	public:
		virtual void initRender() = 0;
		virtual void clearscreen(float colour[4]) = 0;
		virtual void prepRender() = 0;
		virtual void fireRender(int) = 0;
		virtual void postRender() = 0;
		virtual void destroyRender() = 0;
	};
}
#endif