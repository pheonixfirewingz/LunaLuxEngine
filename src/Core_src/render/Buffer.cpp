#include "Buffer.h"
#include "../common/EnginePanic.h"

void LunaLuxEngine::VertexBuffer::create(float* vert, int32 vertcount)
{
	if (lunaLuxEngine::get()->currentAPItype == 0)
		buffer = new OpenGLVertexBuffer();
	else
		EnginePanic::get()->panic("could not create vertexBuffer");

	buffer->create(vert, vertcount);
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
	buffer = nullptr;
}

void LunaLuxEngine::IndexBuffer::create(int* ind, int32 vertcount)
{
	if (lunaLuxEngine::get()->currentAPItype == 0)
		buffer = new OpenGLIndexBuffer();
	else
		EnginePanic::get()->panic("could not create vertexBuffer");

	buffer->create(ind, vertcount);
}

int LunaLuxEngine::IndexBuffer::getIndexCount()
{
	return buffer->getIndexCount();
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
	buffer = nullptr;
}
