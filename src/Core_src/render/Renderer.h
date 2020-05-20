#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/ICamera.h"

namespace LunaLuxEngine
{
	class Renderer
	{
	private:
        Renderer();
        bool nullContext = false;
	public:
        inline static Renderer& get()
		{
			static Renderer* rend = new Renderer();
			return *rend;
		}

		inline bool isNullContext()
        {
            return nullContext;
        }
		void initRender();
		void preRender();
		void Render();
		void postRender();
		void Release();
	};
}
#endif