#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLContext.h"
#include "../window/Window.h"
using namespace LunaLuxEngine;

void LunaLuxEngine::Renderer::pushDataToRenderer(VertexBuffer* buffertorender, IndexBuffer* buffertorender1, Shader* shadertouse)
{
	rbuffer = buffertorender;
	ibuffer = buffertorender1;
	shader = shadertouse;
}

void Renderer::preInitRenderer(int type)
{
	if (type == 0)
	{
		context = new OpenGLContext();
		render = new OGLRenderer();
		LOG("current renderer api set to openGL");
	};
}

void Renderer::initRender()
{
	context->create();
	render->initRender();
	CWin.getNativeWindow()->fireResizeCallback();
};

float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	render->clearscreen(color);
	render->prepRender();
};

void Renderer::Render()
{
	rbuffer->bind();
	ibuffer->bind();
	render->fireRender(ibuffer->getIndexCount());
	rbuffer->unBind();
	ibuffer->unBind();
	context->swapBuffers();
};

void LunaLuxEngine::Renderer::postRender()
{
	render->postRender();
};

void Renderer::Release()
{
	ibuffer->destory();
	rbuffer->destory();
	context->destroy();
	context = nullptr;
	render->destroyRender();
	render = nullptr;
	CWin.destoryWindow();
}