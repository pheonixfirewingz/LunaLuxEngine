#pragma once
#include "../window/Window.h"
namespace LunaLuxEngine
{
	class IRender
	{
	protected:
		bool EnabledDebug = false;
	public:
		inline void toggleDebug()
		{
			if (EnabledDebug) EnabledDebug = false;
			else EnabledDebug = true;
		};

		virtual void initRender(window_api::CrossWindow*) {};

		virtual void prepRender() {};

		virtual void fireRender() {};

		virtual void postRender() {};

		virtual void destroyRender() {};
	};
}