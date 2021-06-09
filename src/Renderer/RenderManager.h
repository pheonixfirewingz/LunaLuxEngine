#pragma once
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <EngineError.h>
#include <Renderer/IRenderer.h>
#include <memory>
#include <utils/EngineDefines.h>

// TODO: write documentation
namespace LunaLux
{
class RenderManager
{
    std::unique_ptr<IRenderer> renderer;
  public:
    enum class API
    {
        DIRECTX12 = 0,
        VULKAN = 1
    };

    static RenderManager* the()
    {
        static auto render = new RenderManager();
        return render;
    }

    EngineResult initialise(API);
    EngineResult RefreshRenderWindow();
    EngineResult update();
    EngineResult cleanUp();
};
} // namespace LunaLux
