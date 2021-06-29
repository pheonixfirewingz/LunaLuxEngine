#include "RenderManager.h"
#include <Renderer/Vulkan/VulkanRenderer.h>
#include <Renderer/DirectX12/DirctX12Renderer.h>
#include <utils/TimeTracker.hpp>

//
// Created by luket on 08/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
// TODO: write documentation
namespace LunaLux
{
EngineResult RenderManager::initialise(API api)
{
    TimeTracker tracker("renderer initialise");
    switch (api)
    {
    case API::DIRECTX12:
        renderer = std::make_unique<DirectX12Renderer>();
        break;
    case API::VULKAN:
        renderer = std::make_unique<VulkanRenderer>();
        break;
    }

    return renderer->initialise(2);
}

EngineResult RenderManager::update()
{
    CHECK(renderer->beginFrame(),"could not start frame")
    //TODO: will do rendering here
    CHECK(renderer->endFrame(),"could not start frame")
    CHECK(renderer->submitToScreen(),"could not submit to window")
    return EngineResult::SUCSESS;
}

EngineResult RenderManager::RefreshRenderWindow()
{
    return renderer->refreshRenderWindow();
}

EngineResult RenderManager::cleanUp()
{
    return renderer->cleanUp();
}
}
