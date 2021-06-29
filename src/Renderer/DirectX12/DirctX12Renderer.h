#pragma once
//
// Created by luket on 29/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
#include <Renderer/IRenderer.h>
// TODO: write documentation
namespace LunaLux
{
#if __has_include(<windows.h>)
class DirectX12Renderer : public IRenderer
{
  public:
    EngineResult initialise(uint8_t uint8) override;
    EngineResult refreshRenderWindow() override;
    EngineResult beginFrame() override;
    EngineResult draw(IRenderable renderable) override;
    EngineResult drawBulk(std::vector<IRenderable> vector) override;
    EngineResult endFrame() override;
    EngineResult submitToScreen() override;
    EngineResult cleanUp() override;
};
#else
class DirectX12Renderer : public IRenderer;
#endif
}