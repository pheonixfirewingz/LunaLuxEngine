#include "OpenGLBuffer.h"

void LunaLuxEngine::OpenGLVertexBuffer::create(float vertex[])
{
	glCreateBuffers(1, &bufferid);
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	unBind();
}

void LunaLuxEngine::OpenGLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, bufferid);
}

void LunaLuxEngine::OpenGLVertexBuffer::unBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LunaLuxEngine::OpenGLVertexBuffer::destory()
{
	glDeleteBuffers(1, &bufferid);
}

void LunaLuxEngine::OpenGLIndexBuffer::create(int ind[])
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	unBind();
}

void LunaLuxEngine::OpenGLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferid);
}

void LunaLuxEngine::OpenGLIndexBuffer::unBind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void LunaLuxEngine::OpenGLIndexBuffer::destory()
{
	glDeleteBuffers(1, &bufferid);
}
