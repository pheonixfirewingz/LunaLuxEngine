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
        IVertexBuffer *buffer;
    public:

        VertexBuffer(float * data, int32 size)
        {
            create(data,size);
        }

        void create(float *, int32);

        void bind();

        void unBind();
    };

    class IndexBuffer
    {
    private:
        IIndexBuffer *buffer;
    public:

        IndexBuffer(int * data, int32 size)
        {
            create(data,size);
        }

        IndexBuffer(unsigned int * data, int32 size)
        {
            create(data,size);
        }

        void create(int *, int32);

        void create(unsigned int *, int32);

        int getIndexCount();

        void bind();

        void unBind();
    };

    class Buffer
    {
    private:
        VertexBuffer* vertexBuffer;
        IndexBuffer* indexBuffer;
    public:
        Buffer(VertexBuffer *vertexBuffer_, IndexBuffer *indexBuffer_)
        {
            vertexBuffer = vertexBuffer_;
            indexBuffer = indexBuffer_;
        };

        Buffer(float * v_data, int32 v_size, int * i_data, int32 i_size)
        {
            vertexBuffer = new VertexBuffer(v_data,v_size);
            indexBuffer  = new IndexBuffer(i_data,i_size);
        };

        Buffer(float * v_data, int32 v_size, unsigned int * i_data, int32 i_size)
        {
            vertexBuffer = new VertexBuffer(v_data,v_size);
            indexBuffer  = new IndexBuffer(i_data,i_size);
        };

        void bind();

        void unBind();

        void bindV();

        void unBindV();

        int getIndexCount();
    };
}
#endif