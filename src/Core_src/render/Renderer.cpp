#include "Renderer.h"
#include "../oldrender/Buffer.h"
#include "../oldrender/Shader.h"
using namespace LunaLuxEngine;

void Renderer::preInitRenderer(GRAPHICS_API_TYPE type)
{
	switch (type)
	{
	case DIRECT_X_ELEVEN:
		render = new DXRenderer();
		break;
		/*case OPEN_GRAPHICS_LOADER:
			render = new OGLRenderer();*/
	}
};

void Renderer::initRender(window_api::CrossWindow* window)
{
	render->initRender(window, instance);
	BufferUtils::get()->giveInstance(instance->getGPUDevice());
	Shaders::get()->giveInstance(instance->getGPUDevice(), instance->getGPUDeviceContext());
	Shaders::get()->compileShader(L"shader.hlsl");
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