//
// Created by luket on 17/08/2020.
//

#ifndef LUNALUXENGINE_WINDOWPANIC_H
#define LUNALUXENGINE_WINDOWPANIC_H
#include "Window.h"
#include <string>
namespace LunaLuxEngine::window_api
{
    class WindowPanic
    {
    public:
        inline static WindowPanic *get()
        {
            static WindowPanic *ep = new WindowPanic();
            return ep;
        }

        [[noreturn]] void panic(std::string);
    };
}
#endif //LUNALUXENGINE_WINDOWPANIC_H
