#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/IRender.h"
#include "DirectX/DirectX.h"
#include "OpenGL/Opengl.h"
#include "../window/Window.h"

namespace LunaLuxEngine
{
	enum GRAPHICS_API_TYPE
	{
		OPEN_GRAPHICS_LOADER = 0,
		VULKAN_ONE_DOT_ONE = 1,
		DIRECT_X_ELEVEN = 2
	};

	class Renderer
	{
	private:
		IRender* render{};

		Renderer()
		{
			render = new DXRenderer();
		};
	public:
		static Renderer* get()
		{
			static Renderer* rend = new Renderer();
			return rend;
		};

		void toggleDebug()
		{
			render->toggleDebug();
		}

		void initRender(window_api::CrossWindow* window)
		{
			render->initRender(window);
		};

		void Render()
		{
			render->prepRender();
			render->fireRender();
			render->postRender();
		};

		void destroyRenderer()
		{
			render->destroyRender();
		};
	};
}
#endif