#include "Renderer.h"
#include <CrossWindow/WindowAPI.h>

LunaLuxEngine::Renderer::Renderer()
{

}

void LunaLuxEngine::Renderer::initRender()
{
    if(nullContext) return;
	CWin.getNativeWindow()->fireResizeCallback();
};

float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
    if(nullContext) return;
};

void LunaLuxEngine::Renderer::Render()
{
    if(nullContext) return;
};

void LunaLuxEngine::Renderer::postRender()
{
    if(nullContext) return;
};

void LunaLuxEngine::Renderer::Release()
{
	CWin.destoryWindow();
}
