#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLContext.h"
#include "../window/Window.h"
using namespace LunaLuxEngine;

void Renderer::preInitRenderer(int8 type)
{
	context = new OpenGLContext();
	render = new OGLRenderer();
}

void Renderer::initRender()
{
	context->create();
	render->initRender();
	CWin.getNativeWindow()->fireResizeCallback();
};

inline void cleanScreen(float colour[4])
{
	glClearColor(colour[0], colour[1], colour[2], colour[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}

float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	cleanScreen(color);
	render->prepRender();
};

void Renderer::Render()
{
	render->fireRender();
	context->swapBuffers();
};

void LunaLuxEngine::Renderer::postRender()
{
	render->postRender();
};

void Renderer::Release()
{
	context->destroy();
	context = nullptr;
	render->destroyRender();
	render = nullptr;
	CWin.destoryWindow();
}