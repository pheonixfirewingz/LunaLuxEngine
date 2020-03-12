#ifndef LUNALUXENGINE_OPENGLBUFFER_H
#define LUNALUXENGINE_OPENGLBUFFER_H
#include "../Common/IBuffer.h"
#include <glad/glad.h>
namespace LunaLuxEngine
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
		unsigned int bufferid;
	public:
		void create(float[]) override;
		void bind() override;
		void unBind() override;
		void destory() override;
	};

	class OpenGLIndexBuffer : public IIndexBuffer
	{
		unsigned int bufferid;
	public:
		void create(int[]) override;
		void bind() override;
		void unBind() override;
		void destory() override;
	};
}
#endif
