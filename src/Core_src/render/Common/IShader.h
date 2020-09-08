#ifndef LUNALUXENGINE_ISHADER_H
#define LUNALUXENGINE_ISHADER_H

#include <LLESDK/types.h>

namespace LunaLuxEngine
{
    class IShader
    {
    public:
        virtual void create(char *, int) = 0;

        virtual void bind(int) = 0;

        virtual void unBind(int) = 0;

        virtual void link(int) = 0;

        virtual void use(int) = 0;
    };
}

#endif
