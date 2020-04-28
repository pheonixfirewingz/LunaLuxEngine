#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLContext.h"
using namespace LunaLuxEngine;

LunaLuxEngine::Renderer::Renderer()
{

}
int boot = 0;
void LunaLuxEngine::Renderer::pushDataToRenderer(VertexBuffer& vertexbuffer, IndexBuffer& indexbuffer, Shader& shader_)
{
	if (boot == 1)
	{
		rbuffer.destory();
		ibuffer.destory();
		shader.destory();
	}
	else boot++;

	rbuffer = vertexbuffer;
	ibuffer = indexbuffer;
	shader = shader_;
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
	rbuffer.bind();
	ibuffer.bind();
	render->fireRender(ibuffer.getIndexCount());
	rbuffer.unBind();
	ibuffer.unBind();
	context->swapBuffers();
};

void LunaLuxEngine::Renderer::postRender()
{
	render->postRender();
};

void Renderer::Release()
{
	ibuffer.destory();
	rbuffer.destory();
	context->destroy();
	context = nullptr;
	render->destroyRender();
	render = nullptr;
	CWin.destoryWindow();
}

/*void Renderer::setCamera(ICamera& cam)
{
	camera = cam;
}*/
