#include "Renderer.h"
using namespace LunaLuxEngine;

void Renderer::preInitRenderer(GRAPHICS_API_TYPE type)
{
	switch (type)
	{
	case DIRECT_X_ELEVEN:
		render = new DXRenderer();
		break;
	case OPEN_GRAPHICS_LOADER:
		render = new OGLRenderer();
	}
};

void Renderer::initRender(window_api::CrossWindow* window)
{
	render->initRender(window);
};

void LunaLuxEngine::Renderer::preRender()
{
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

void Renderer::destroyRenderer()
{
	render->destroyRender();
};