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

void Renderer::Render()
{
	render->prepRender();
	render->fireRender();
	render->postRender();
};

void Renderer::destroyRenderer()
{
	render->destroyRender();
};