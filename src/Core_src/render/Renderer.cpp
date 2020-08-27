#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"

LunaLuxEngine::Renderer::Renderer()
{
    render = new OGLRenderer();
}

void LunaLuxEngine::Renderer::preRender()
{
    render->clearscreen(color);
    render->prepRender();
}

void LunaLuxEngine::Renderer::Render()
{
    shader->use();
    buffer->bind();
    texture->bind();
    layout->bindLayoutToRenderer();
    render->fireRender(buffer->getIndexCount());
    layout->unbindLayoutToRenderer();
    texture->unbind();
    buffer->unBind();
}