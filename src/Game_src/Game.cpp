//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>

using namespace LunaLuxEngine::window_api;
#include "Game.h"
#include "../Core_src/render/OpenGL/OpenGLUtils.h"
#include "../Core_src/fs/FileManager.h"
#include <GLM/gtc/matrix_transform.hpp>

glm::mat4 model = glm::mat4(1.0f), view = glm::mat4(1.0f), projection = glm::mat4(1.0f);

void PublicGame::preBoot()
{
	PublicGame::setGameName((int8*)"TestGame");
	PublicGame::setWindowSize(1280, 720);
}

float vertices[] = {0.5f,0.5f,0.0f,1.0f,1.0f,0.5f,-0.5f,0.0f,1.0f,0.0f,-0.5f,-0.5f,0.0f,0.0f,0.0f,-0.5f,0.5f,0.0f,0.0f,1.0f};
unsigned int indices[] = {0,1,2,0,2,3};
LunaLuxEngine::Shader* shader;
LunaLuxEngine::Buffer* buffer;
LunaLuxEngine::Texture* texture;

void PublicGame::GameBoot()
{
    std::vector<LunaLuxEngine::SHADERLAYOUTTYPE> types;
    types.push_back(LunaLuxEngine::SHADERLAYOUTTYPE::FLOAT3);
    types.push_back(LunaLuxEngine::SHADERLAYOUTTYPE::FLOAT2);

    buffer = new LunaLuxEngine::Buffer(vertices, sizeof(vertices),indices, sizeof(indices));

    shader = new LunaLuxEngine::Shader(LunaLuxEngine::FileManager::get()->readShaderFile("resources/shader",true).data(),
                                      LunaLuxEngine::FileManager::get()->readShaderFile("resources/shader",false).data());

    texture = new LunaLuxEngine::Texture(LunaLuxEngine::FileManager::get()->getAbsolutePath("resources/Disco-Dingo.jpg"),0);
    LunaLuxEngine::OpenGLUtils::setInt(shader->getOGLSID(),"texture1",0);

    LunaLuxEngine::Renderer::get().setClearColour(0.3f, 0.3f, 0.9f, 1.0f);
    LunaLuxEngine::Renderer::get().submit(buffer,shader,types,texture);

    model = glm::translate(model,glm::vec3(0.0f,0.0f,-2.0f));
    projection = glm::perspective(glm::radians(45.0f),CWin.getAspectRatio(),0.1f,100.0f);
}

void PublicGame::GameUpdate()
{
    //temp for debug----
    if (CWin.getNativeWindow()->getInputController()->isKeyDown(LLE_KEY_1)) CWin.setShouldClose(true);
    //-----------------------
    LunaLuxEngine::OpenGLUtils::setMat4(shader->getOGLSID(), "model", model);
    LunaLuxEngine::OpenGLUtils::setMat4(shader->getOGLSID(), "view", view);
    LunaLuxEngine::OpenGLUtils::setMat4(shader->getOGLSID(), "projection", projection);
}

void PublicGame::GameLevel() {}
