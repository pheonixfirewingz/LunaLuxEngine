#include "Buffer.h"
#include "OpenGL/OpenGLBuffer.h"
void LunaLuxEngine::VertexBuffer::create(int8 type)
{
	buffer = new OpenGLVertexBuffer();
}

void LunaLuxEngine::VertexBuffer::pushData(float ind[])
{
	buffer->create(ind);
}

void LunaLuxEngine::VertexBuffer::bind()
{
	buffer->bind();
}

void LunaLuxEngine::VertexBuffer::unBind()
{
	buffer->unBind();
}

void LunaLuxEngine::VertexBuffer::destory()
{
	buffer->destory();
}

void LunaLuxEngine::IndexBuffer::create(int8  type)
{
	buffer = new OpenGLIndexBuffer();
}

void LunaLuxEngine::IndexBuffer::pushData(int vert[])
{
	buffer->create(vert);
}

void LunaLuxEngine::IndexBuffer::bind()
{
	buffer->bind();
}

void LunaLuxEngine::IndexBuffer::unBind()
{
	buffer->unBind();
}

void LunaLuxEngine::IndexBuffer::destory()
{
	buffer->destory();
}
