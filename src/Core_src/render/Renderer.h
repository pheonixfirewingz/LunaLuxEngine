#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/IRender.h"
#include "Common/GPUInstance.h"

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
	public:
		GPUInstance& instance = GPUInstance::getInstance();
		inline static Renderer* get()
		{
			static Renderer* rend = new Renderer();
			return rend;
		};

		void preInitRenderer(int8);
		void initRender();
		void preRender();
		void Render();
		void postRender();
		void Release();
	};
}
#endif