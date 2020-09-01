#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLUtils.h"

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

void LunaLuxEngine::Renderer::beginLevel(LunaLuxEngine::Camera & camera)
{
    LunaLuxEngine::OpenGLUtils::setMat4(shader->getOGLSID(), "projection", camera.getProjectionMatrix());
}

void LunaLuxEngine::Renderer::endLevel()
{

}
