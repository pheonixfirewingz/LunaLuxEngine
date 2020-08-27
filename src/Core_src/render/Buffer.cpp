#include "Buffer.h"
#include "../common/EnginePanic.h"

void LunaLuxEngine::VertexBuffer::create(float *vert, int32 vertcount)
{
    buffer = new OpenGLVertexBuffer();
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

void LunaLuxEngine::IndexBuffer::create(int *ind, int32 vertcount)
{
    buffer = new OpenGLIndexBuffer();
    buffer->create(ind, vertcount);
}

void LunaLuxEngine::IndexBuffer::create(unsigned int *ind, int32 vertcount)
{
    buffer = new OpenGLIndexBuffer();
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

void LunaLuxEngine::Buffer::bind()
{
    vertexBuffer->bind();
    indexBuffer->bind();
}

void LunaLuxEngine::Buffer::unBind()
{
    indexBuffer->unBind();
    vertexBuffer->unBind();
}

int LunaLuxEngine::Buffer::getIndexCount()
{
    return indexBuffer->getIndexCount();
}

void LunaLuxEngine::Buffer::bindV()
{
    vertexBuffer->bind();
}

void LunaLuxEngine::Buffer::unBindV()
{
    vertexBuffer->unBind();
}
