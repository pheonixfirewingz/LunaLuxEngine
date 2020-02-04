#pragma once

#include <LLESDK/Common_Header.h>
#include "../window/Window.h"
namespace LunaLuxEngine
{
	class IRender
	{
	public:
		void initRender(window_api::CrossWindow*);

		void prepRender();

		void fireRender();

		void destroyRender();
	};
}