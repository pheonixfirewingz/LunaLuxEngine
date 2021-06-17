//
// Created by luket on 08/06/2021.
//
// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
//
#include "LunaLuxEngine.h"
#include <LunaLux/WindowLib.h>
#include <EngineError.h>
#include <utils/TimeTracker.hpp>
// TODO: write documentation
namespace LunaLux
{
EngineResult LunaLuxEngine::initialise()
{
    LunaLux::windowCreate("LunaLuxEngine - Dev Build",1280,720);
    TimeTracker tracker("main initialise");

    renderManager = std::make_unique<RenderManager>();
    CHECK(renderManager->initialise(RenderManager::API::VULKAN),"failed to load renderer")


    return EngineResult::SUCSESS;
}

EngineResult LunaLuxEngine::update()
{
    //------------------------------------------------------------
    // HANDLE OPERATING SYSTEM WINDOW
    //------------------------------------------------------------
    windowUpdate();
    if(hasWindowResized())
    {
        renderManager->RefreshRenderWindow();
    }
    //------------------------------------------------------------
    renderManager->update();
    return EngineResult::SUCSESS;
}

EngineResult LunaLuxEngine::cleanUp()
{
    CHECK(renderManager->cleanUp(),"could not clean up renderer")
    (void)renderManager.release();
    windowClose();
    return EngineResult::SUCSESS;
}

void LunaLuxEngine::run()
{
    initialise();
    while (!shouldCloseWindow())
    {
        update();
    }
    cleanUp();
}
}
