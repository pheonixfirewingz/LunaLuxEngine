#ifndef LUNALUXENGINE_IRENDER_H
#define LUNALUXENGINE_IRENDER_H

#include <LLESDK/types.h>

namespace LunaLuxEngine
{
    class IRender
    {
    public:
        virtual void clearscreen(float colour[4]) = 0;

        virtual void prepRender() = 0;

        virtual void fireRender(int) = 0;
    };
}
#endif