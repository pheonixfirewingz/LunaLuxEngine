#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/ICamera.h"

namespace LunaLuxEngine
{
	class Renderer
	{
	private:
        Renderer();
        ~Renderer();
	public:
        inline static Renderer& get()
		{
			static Renderer* rend = new Renderer();
			return *rend;
		}

		void preRender();
		void Render();
		void postRender();
	};
}
#endif