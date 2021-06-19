#pragma once
//
// Created by luket on 05/04/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <utils/EngineDefines.h>
//TODO: write documentation
namespace LunaLux
{
class NetworkManager
{
  public:
    EngineResult initialise();
    EngineResult cleanUp();
};
}