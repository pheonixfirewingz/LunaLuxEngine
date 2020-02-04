#pragma once

#include <LLESDK/Common_Header.h>
#include "../window/Window.h"
namespace LunaLuxEngine
{
	class IRender
	{
	public:
		virtual void initRender(window_api::CrossWindow*) {};

		virtual void prepRender() {};

		virtual void fireRender() {};

		virtual void destroyRender() {};
	};
}