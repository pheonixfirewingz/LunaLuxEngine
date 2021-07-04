//
// Created by luket on 08/06/2021.
//

#include "EngineError.h"
#include <cstdio>
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
namespace LunaLux
{
void HandleError(EngineResult result,const std::string& error)
{
    switch (result)
    {
    case EngineResult::SUCSESS: break;
    case EngineResult::DIRECTX_TWELVE_ERROR:
        printf("LunaLuxEngine - DIRECTX_TWELVE_ERROR: %s\n",error.c_str());
        break;
    case EngineResult::VULKAN_ERROR:
        printf("LunaLuxEngine - VULKAN_ERROR: %s\n",error.c_str());
        break;
    case EngineResult::ENGINE_ERROR:
        printf("LunaLuxEngine - ENGINE_ERROR: %s\n",error.c_str());
        break;
    }
}
}
