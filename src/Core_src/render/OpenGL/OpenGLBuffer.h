#ifndef LUNALUXENGINE_OPENGLBUFFER_H
#define LUNALUXENGINE_OPENGLBUFFER_H
#include "../Common/IBuffer.h"
#include <algorithm>
#include <vector>
namespace LunaLuxEngine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	private:
		unsigned int vertexbuffer;
	public:
		void create(float* vert, int32 vertcount) override;
		void bind() override;
		void unBind() override;
		void destory() override;
	};

	class OpenGLIndexBuffer : public IIndexBuffer
	{
        unsigned int indexbuffer;
	public:
		void create(int* index, int32 indexcount) override;
		void bind() override;
		void unBind() override;
		void destory() override;
	};
}
#endif
