#include "Renderer.h"
#include "../oldrender/Buffer.h"
#include "../oldrender/Shader.h"
using namespace LunaLuxEngine;

void Renderer::preInitRenderer(int8 type)
{
	switch (type)
	{
	case DIRECT_X_ELEVEN:
		render = new DXRenderer();
		break;
	}
};

void Renderer::initRender()
{
	render->initRender(instance);
};

float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	instance->cleanScreen(color);
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
	Shaders::get()->clearShaders();
	BufferUtils::get()->releaseBuffers();
	instance->Release();
};