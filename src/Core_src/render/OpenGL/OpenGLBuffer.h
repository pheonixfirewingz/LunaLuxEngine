#ifndef LUNALUXENGINE_OPENGLBUFFER_H
#define LUNALUXENGINE_OPENGLBUFFER_H
#include "../Common/IBuffer.h"
#include "glad.h"
#include <algorithm>
#include <vector>
namespace LunaLuxEngine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	private:
		GLuint vertexbuffer;
	public:
	    ~OpenGLVertexBuffer();
		void create(float* vert, int32 vertcount) override;
		void bind() override;
		void unBind() override;
	};

	class OpenGLIndexBuffer : public IIndexBuffer
	{
		GLuint indexbuffer;
	public:
	    ~OpenGLIndexBuffer();
		void create(int* index, int32 indexcount) override;
        void create(unsigned int* index, int32 indexcount) override;
		void bind() override;
		void unBind() override;
	};
}
#endif
