//
// Created by luket on 20/05/2020.
//

#ifndef LUNALUXENGINE_GAA_HPP
#define LUNALUXENGINE_GAA_HPP

#include <WindowAPI.h>

namespace LunaLuxEngine::GAA
{
    enum class GAAReturnType
    {
        GAA_OK = 0,
        GAA_NOT_OK = 1,
    };

    GAAReturnType GAAInit(window_api::IWindow&);
    void GAATerminate();
};
#endif //LUNALUXENGINE_GAA_HPP
