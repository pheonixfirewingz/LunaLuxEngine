#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/IRender.h"
#include "Common/IContext.h"
#include "Buffer.h"
#include "Shader.h"

namespace LunaLuxEngine
{
	class Renderer
	{
	private:
		IRender* render{};
		IContext* context{};
		VertexBuffer* rbuffer;
		IndexBuffer* ibuffer;
		Shader* shader;
	public:
		inline static Renderer* get()
		{
			static Renderer* rend = new Renderer();
			return rend;
		};

		void pushDataToRenderer(VertexBuffer* buffertorender, IndexBuffer* buffertorender1, Shader* shadertouse);
		void preInitRenderer(int);
		void initRender();
		void preRender();
		void Render();
		void postRender();
		void Release();
	};
}
#endif