#include "OpenGLBuffer.h"
#include <iostream>

void LunaLuxEngine::OpenGLVertexBuffer::create(float *vert, int32 vertcount)
{
    vertcount_ = vertcount;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertcount, vert, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LunaLuxEngine::OpenGLVertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
}

void LunaLuxEngine::OpenGLVertexBuffer::unBind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

LunaLuxEngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &vertexbuffer);
}

void LunaLuxEngine::OpenGLIndexBuffer::create(int *index, int32 indexcount)
{
    indexcount_ = indexcount;
    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount, index, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void LunaLuxEngine::OpenGLIndexBuffer::create(unsigned int *index, int32 indexcount)
{
    indexcount_ = indexcount;
    glGenBuffers(1, &indexbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexcount, index, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void LunaLuxEngine::OpenGLIndexBuffer::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
}

void LunaLuxEngine::OpenGLIndexBuffer::unBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

LunaLuxEngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &indexbuffer);
}
