#ifndef LUNALUXENGINE_RENDERER_H
#define LUNALUXENGINE_RENDERER_H
#include "Common/IRender.h"
#include "Common/IContext.h"
#include "Common/ICamera.h"
#include "Buffer.h"
#include "Shader.h"

namespace LunaLuxEngine
{
	class Renderer
	{
	private:
        Renderer();
		//ICamera& camera;
		IRender* render;
		IContext* context;
		VertexBuffer& rbuffer = *new VertexBuffer();
		IndexBuffer& ibuffer = *new IndexBuffer();
		Shader& shader  = *new Shader();
	public:
        inline static Renderer& get()
		{
			static Renderer* rend = new Renderer();
			return *rend;
		}
		void pushDataToRenderer(VertexBuffer&, IndexBuffer&, Shader&);
		//void setCamera(ICamera&);
		void preInitRenderer(int);
		void initRender();
		void preRender();
		void Render();
		void postRender();
		void Release();
	};
}
#endif