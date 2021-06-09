#pragma once
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <Renderer/IRenderable.h>
#include <cstdint>
#include <utils/EngineDefines.h>
#include <vector>
// TODO: write documentation
namespace LunaLux
{
class IRenderer
{
  public:
    struct FlightFrame
    {
        uint8_t frame_id = 0;
        EngineResult result = EngineResult::SUCSESS;
    };

    virtual EngineResult initialise(uint8_t) = 0;
    virtual EngineResult refreshRenderWindow() = 0;
    virtual EngineResult beginFrame() = 0;
    virtual EngineResult draw(IRenderable) = 0;
    virtual EngineResult drawBulk(std::vector<IRenderable>) = 0;
    virtual EngineResult endFrame() = 0;
    virtual EngineResult submitToScreen() = 0;
    virtual EngineResult cleanUp() = 0;
};
}
