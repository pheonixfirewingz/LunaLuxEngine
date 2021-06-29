#if __has_include(<windows.h>)
#include "DirctX12Renderer.h"
#include <LunaLux/DirectX12Lib.h>
#include <LunaLux/WindowLib.h>
//
// Created by luket on 29/06/2021.
//

// GNU Lesser General Public License Version 2.1
//
// Copyright Luke Shore (c) 2020, 2021
// TODO: write documentation
namespace LunaLux
{

EngineResult DirectX12Renderer::initialise(uint8_t max_frames_in_flight)
{
    directx12Init(reinterpret_cast<HWND>(windowGetNative()),windowGetRectSize());
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::refreshRenderWindow()
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::beginFrame()
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::draw(IRenderable renderable)
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::drawBulk(std::vector<IRenderable> vector)
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::endFrame()
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::submitToScreen()
{
    return EngineResult::SUCSESS;
}
EngineResult DirectX12Renderer::cleanUp()
{
    return EngineResult::SUCSESS;
}
}
#endif