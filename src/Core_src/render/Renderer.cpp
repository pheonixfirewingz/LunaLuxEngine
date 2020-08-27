#include "Renderer.h"
#include "OpenGL/OpenGLRenderer.h"
#include "OpenGL/OpenGLUtils.h"
#include "../fs/FileManager.h"
#include <CrossWindow/WindowAPI.h>
#include <GLM/gtc/matrix_transform.hpp>

LunaLuxEngine::Renderer::Renderer()
{
    render = new OGLRenderer();
    vbuffer = new VertexBuffer();
    ibuffer = new IndexBuffer();
    shader = new Shader();
    layout = new ShaderLayout();
    texture = new OpenGLTexture(FileManager::get()->getAbsolutePath("resources/Disco-Dingo.jpg"),0);
    glEnable(GL_TEXTURE_2D);
}

float vertices[] =
        {
                // positions       // texture coords
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f,   // top right
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,   // bottom right
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,   // bottom left
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f    // top left
        };
unsigned int indices[] =
        {
                0, 1, 2, 0, 2, 3,};

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

void LunaLuxEngine::Renderer::initRender()
{
    obj_data data = FileManager::get()->loadObj("resources/cube.obj");
    LOG("Renderer::initRender() is deprecated")

    vbuffer->create(vertices, sizeof(vertices));
    ibuffer->create(indices, sizeof(indices));

    std::vector<SHADERLAYOUTTYPE> types;

    types.push_back(SHADERLAYOUTTYPE::FLOAT3);
    types.push_back(SHADERLAYOUTTYPE::FLOAT2);


    vbuffer->bind();
    layout->setupShaderLayout(types);
    vbuffer->unBind();

    shader->compile(FileManager::get()->readShaderFile("resources/shader",true).data(),
                    FileManager::get()->readShaderFile("resources/shader", false).data());

    OpenGLUtils::setInt(shader->getOGLSID(), "texture1", 0);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f),CWin.getAspectRatio(),0.1f, 100.0f);
}

float color[4] = {0.3f, 0.3f, 0.9f, 1.0f};

void LunaLuxEngine::Renderer::preRender()
{
    render->clearscreen(color);
    render->prepRender();
}


void LunaLuxEngine::Renderer::Render()
{
    view = glm::rotate(view, 15.0f, glm::vec3(0.0f, 0.0f, 0.1f));

    shader->use();
    OpenGLUtils::setMat4(shader->getOGLSID(), "model", model);
    OpenGLUtils::setMat4(shader->getOGLSID(), "view", view);
    OpenGLUtils::setMat4(shader->getOGLSID(), "projection", projection);
    texture->bind();
    vbuffer->bind();
    ibuffer->bind();
    layout->bindLayoutToRenderer();
    render->fireRender(ibuffer->getIndexCount());
    layout->unbindLayoutToRenderer();
    texture->unbind();
    vbuffer->unBind();
    ibuffer->unBind();
}
