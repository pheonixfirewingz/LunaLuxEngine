#pragma once
//
// Created by luket on 29/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Renderer/IRenderer.h>
#include <utils/BinaryTree.hpp>
// TODO: write documentation
namespace LunaLux
{
#if __has_include(<windows.h>)
class DirectX12Renderer : public IRenderer
{
  public:
    EngineResult initialise(uint8_t frames_in_flight) final;
    EngineResult refreshRenderWindow() final;
    EngineResult beginFrame() final;
    EngineResult draw(Component<Entity> entity) final;
    EngineResult endFrame() final;
    EngineResult submitToScreen() final;
    EngineResult cleanUp() final;
};
#endif
}