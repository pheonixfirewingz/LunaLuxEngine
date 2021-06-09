#pragma once
//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include <Renderer/IRenderer.h>
#include <vector>
#include <Renderer/Vulkan/Utils/Fence.hpp>
#include <Renderer/Vulkan/Utils/Semaphore.hpp>
// TODO: write documentation
namespace LunaLux
{
class VulkanRenderer : public IRenderer
{
    std::vector<Semaphore>  image_acquired;
    std::vector<Semaphore>  draw_complete;
    std::vector<Semaphore>  image_ownership;
    std::vector<Fence>      fences;
  public:
    EngineResult initialise(uint8_t) final;
    EngineResult refreshRenderWindow() final;
    EngineResult beginFrame() final;
    EngineResult draw(IRenderable renderable) final;
    EngineResult drawBulk(std::vector<IRenderable> vector) final;
    EngineResult endFrame() override;
    EngineResult submitToScreen() final;
    EngineResult cleanUp() final;
};
} // namespace LunaLux
