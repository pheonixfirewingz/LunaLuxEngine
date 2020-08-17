#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/IRender.h"
#include "Buffer.h"
#include "Shader.h"

namespace LunaLuxEngine
{
	class Renderer
	{
	private:
        Renderer();
        ~Renderer();
		//ICamera& camera;
		IRender* render;
		VertexBuffer& vbuffer = *new VertexBuffer();
		IndexBuffer& ibuffer = *new IndexBuffer();
		Shader& shader  = *new Shader();
	public:
        inline static Renderer& get()
		{
			static Renderer* rend = new Renderer();
			return *rend;
		}
		void initRender();
		void beginLevel();
		void endLevel();
		void preRender();
		void Render();
	};
}
#endif