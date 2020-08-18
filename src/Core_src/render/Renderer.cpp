#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLUtils.h"
#include "../fs/FileManager.h"
#include <CrossWindow/WindowAPI.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

LunaLuxEngine::Renderer::Renderer()
{
    render = new OGLRenderer();
    vbuffer = new VertexBuffer();
    ibuffer = new IndexBuffer();
    shader  = new Shader();
    texture = new OpenGLTexture(FileManager::get()->getAbsolutePath("resources/Disco-Dingo.jpg"));
    glEnable(GL_TEXTURE_2D);
}

void LunaLuxEngine::Renderer::beginLevel()
{

}

void LunaLuxEngine::Renderer::endLevel()
{

}

float vertices[] =
{
        // positions       // texture coords
        0.5f,  0.5f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f, 0.0f, 1.0f    // top left
};
unsigned int indices[] =
{
    0, 1, 2,
    0, 2, 3,
};

void LunaLuxEngine::Renderer::initRender()
{
    LOG("Renderer::initRender() is deprecated");
	CWin.getNativeWindow()->fireResizeCallback();

    vbuffer->create(vertices, sizeof(vertices));
    ibuffer->create(indices, sizeof(indices));
    vbuffer->bind();
    //----------this is part of the layout abstract to be removed when complete--------------------
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //---------------------------------------------------------------------------------------------------------
    vbuffer->unBind();

    shader->compile( FileManager::get()->readFile("resources/vertex.glsl").data(),
                    FileManager::get()->readFile("resources/fragment.glsl").data());
    OpenGLUtils::setInt(shader->getOGLSID(),"texture1", 0);
}

float color[4] = { 0.3f, 0.3f, 0.9f, 1.0f };
void LunaLuxEngine::Renderer::preRender()
{
	render->clearscreen(color);
	render->prepRender();
}
float rot = 0.0f;
void LunaLuxEngine::Renderer::Render()
{
    if(CWin.getNativeWindow()->getInputController()->isKeyDown(window_api::LLE_KEY_R)) rot++;
    if(CWin.getNativeWindow()->getInputController()->isKeyDown(window_api::LLE_KEY_T)) rot--;
    glActiveTexture(GL_TEXTURE0);
    shader->use();
    glm::mat4 model         = glm::mat4(1.0f);
    glm::mat4 view          = glm::mat4(1.0f);
    glm::mat4 projection    = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)CWin.getNativeWindow()->getWindowW() / CWin.getNativeWindow()->getWindowH(), 0.1f, 100.0f);
    unsigned int modelLoc = glGetUniformLocation(shader->getOGLSID(), "model"),
            viewLoc  = glGetUniformLocation(shader->getOGLSID(), "view");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    OpenGLUtils::setMat4(shader->getOGLSID(),"projection", projection);

    texture->bind();
    vbuffer->bind();
    ibuffer->bind();
    render->fireRender(ibuffer->getIndexCount());
    texture->unbind();
    vbuffer->unBind();
    ibuffer->unBind();
}