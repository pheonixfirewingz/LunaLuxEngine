#ifndef LUNALUXENGINE_BUFFER_H
#define LUNALUXENGINE_BUFFER_H
#include "Common/IBuffer.h"
#include <LLESDK/types.h>
namespace LunaLuxEngine
{
	class VertexBuffer
	{
		IVertexBuffer* buffer;
		unsigned int vertCount;
	public:
		void create(int8);
		void pushData(float[]);
		void bind();
		void unBind();
		void destory();
	};

	class IndexBuffer
	{
		IIndexBuffer* buffer;
		unsigned int indCont;
	public:
		void create(int8);
		void pushData(int[]);
		void bind();
		void unBind();
		void destory();
	};
}
#endif