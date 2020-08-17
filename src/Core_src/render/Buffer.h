#ifndef LUNALUXENGINE_BUFFER_H
#define LUNALUXENGINE_BUFFER_H
#include "Common/IBuffer.h"
#include "OpenGL/OpenGLBuffer.h"
#include <LLESDK/types.h>
#include "../LunaLuxEngineCore.h"

namespace LunaLuxEngine
{
	class VertexBuffer
	{
	private:
		IVertexBuffer* buffer;
	public:
		void create(float*, int32);
		void bind();
		void unBind();
	};

	class IndexBuffer
	{
	private:
		IIndexBuffer* buffer;
	public:
		void create(int*, int32);
		int getIndexCount();
		void bind();
		void unBind();
	};
}
#endif