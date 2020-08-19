#ifndef LUNALUXENGINE_IBUFFER_H
#define LUNALUXENGINE_IBUFFER_H

#include <LLESDK/types.h>

namespace LunaLuxEngine
{
    class IVertexBuffer
    {
    protected:
        int32 vertcount_;
    public:
        int32 getVertCount()
        { return vertcount_; };

        virtual void create(float *verts, int32 vertcount) = 0;

        virtual void bind() = 0;

        virtual void unBind() = 0;
    };

    class IIndexBuffer
    {
    protected:
        int32 indexcount_;
    public:
        int32 getIndexCount()
        { return indexcount_; };

        virtual void create(int *index, int32 indexcount) = 0;

        virtual void create(unsigned int *index, int32 indexcount) = 0;

        virtual void bind() = 0;

        virtual void unBind() = 0;
    };
}
#endif
