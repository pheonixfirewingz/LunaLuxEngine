#pragma once
//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
#include <Renderer/RenderManager.h>
#include <memory>
#include <utils/EngineDefines.h>
namespace LunaLux
{
class LunaLuxEngine
{
    std::unique_ptr<RenderManager> renderManager;
    EngineResult initialise();
    EngineResult update();
    EngineResult cleanUp();
  public:
    void run();
};
} // namespace LunaLux
