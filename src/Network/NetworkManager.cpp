#include "NetworkManager.h"
//
// Created by luket on 05/04/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <LunaLux/NetLib.h>
//TODO: write documentation
namespace LunaLux
{
EngineResult NetworkManager::initialise()
{
    if(net::netInit() != LunaLux::net::NetResult::SUCSESS)
    {
        return EngineResult::ENGINE_ERROR;
    }

    return EngineResult::SUCSESS;
}

EngineResult NetworkManager::cleanUp()
{
    net::terminate();
    return EngineResult::SUCSESS;
}
}