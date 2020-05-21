#include "Renderer.h"
#include "../common/EnginePanic.h"
#include <CrossWindow/WindowAPI.h>
#include <GAA/GAA.h>

LunaLuxEngine::Renderer::Renderer()
{
    LOG("Loading Graphics API Abstraction Layer")
    if(GAA::GAAInit(CWin) != GAA::GAAReturnType::GAA_OK) EnginePanic::get()->panic("could not create GAA Context");
    CWin.getNativeWindow()->fireResizeCallback();
}

float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
}

void LunaLuxEngine::Renderer::Render()
{
    GAA::GAAUpdate(CWin);
}

void LunaLuxEngine::Renderer::postRender()
{
}

LunaLuxEngine::Renderer::~Renderer()
{
    GAA::GAATerminate(CWin);
};
