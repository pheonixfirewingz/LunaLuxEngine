#include "Renderer.h"
#include "../common/EnginePanic.h"
#include <CrossWindow/WindowAPI.h>
#include <GAA/GAA.h>

LunaLuxEngine::Renderer::Renderer()
{
    LOG("Loading Graphics API Abstraction Layer")
    if(GAA::GAAInit(CWin,false) != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("could not create GAA Context");
    CWin.getNativeWindow()->fireResizeCallback();
}

float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
    if(GAA::GAA_pre_render() != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("GAA failed");
}

void LunaLuxEngine::Renderer::Render()
{
    if(GAA::GAAUpdate(CWin) != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("GAA failed");
    if(GAA::GAA_render() != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("GAA failed");
}

void LunaLuxEngine::Renderer::postRender()
{
    if(GAA::GAA_post_render() != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("GAA failed");
}

LunaLuxEngine::Renderer::~Renderer()
{
    GAA::GAATerminate(CWin);
};
