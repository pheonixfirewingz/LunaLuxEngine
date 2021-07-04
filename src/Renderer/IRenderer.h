#pragma once
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <EntitySystem/Entity.h>
#include <cstdint>
#include <utils/BinaryTree.hpp>
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

    virtual EngineResult initialise(uint8_t frames_in_flight) = 0;
    virtual EngineResult refreshRenderWindow() = 0;
    virtual EngineResult beginFrame() = 0;
    virtual EngineResult draw(Component<Entity> entity) = 0;
    virtual EngineResult endFrame() = 0;
    virtual EngineResult submitToScreen() = 0;
    virtual EngineResult cleanUp() = 0;
};
}
