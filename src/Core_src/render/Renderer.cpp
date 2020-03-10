#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
using namespace LunaLuxEngine;

void Renderer::preInitRenderer(int8 type)
{
	render = new OGLRenderer();
}

void Renderer::initRender()
{
	render->initRender();
	CWin.fireResizeCallback();
};

float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	instance.cleanScreen(color);
	render->prepRender();
};

void Renderer::Render()
{
	render->fireRender();

};

void LunaLuxEngine::Renderer::postRender()
{
	render->postRender();
};

void Renderer::Release()
{
	render->destroyRender();
	render = nullptr;
	instance.Release();
	CWin.destoryWindow();
}