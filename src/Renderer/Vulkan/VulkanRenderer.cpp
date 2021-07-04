//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
#include "VulkanRenderer.h"
#include <LunaLux/VulkanLib.h>
#include <LunaLux/VulkanUtilLib.h>
#include <LunaLux/WindowLib.h>
namespace LunaLux
{
EngineResult VulkanRenderer::initialise(uint8_t frames_in_flight)
{
    vulkanInit(windowGetNative(),windowGetRectSize());
    for (uint8_t i = 0; i < frames_in_flight; i++)
    {
        image_acquired.emplace_back();
        draw_complete.emplace_back();
        image_ownership.emplace_back();
        fences.emplace_back((VK_FENCE_CREATE_SIGNALED_BIT));
    }
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::refreshRenderWindow()
{
    LunaLux::vulkanResizeSwapChain(windowGetRectSize());
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::beginFrame()
{
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::draw(Component<Entity> entity)
{
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::endFrame()
{
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::submitToScreen()
{
    return EngineResult::SUCSESS;
}

EngineResult VulkanRenderer::cleanUp()
{
    vkDeviceWaitIdle();
    for (Semaphore& item: image_acquired) item.clear();
    for (Semaphore& item: draw_complete) item.clear();
    for (Semaphore& item: image_ownership) item.clear();
    for (Fence& item: fences) item.clear();

    vulkanCleanUp();
    return EngineResult::SUCSESS;
}
}