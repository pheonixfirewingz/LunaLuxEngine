//
// Created by luket on 23/01/2020.
//
#include <CrossWindow/WindowAPI.h>

using namespace LunaLuxEngine::window_api;
#include "Game.h"
#include "../Core_src/render/OpenGL/OpenGLUtils.h"
#include <GLM/gtc/matrix_transform.hpp>

using namespace LunaLuxEngine;

glm::mat4 model = glm::mat4(1.0f), view = glm::mat4(1.0f);

float vertices[] = {0.5f,0.5f,0.0f,1.0f,1.0f,0.5f,-0.5f,0.0f,1.0f,0.0f,-0.5f,-0.5f,0.0f,0.0f,0.0f,-0.5f,0.5f,0.0f,0.0f,1.0f};
unsigned int indices[] = {0,1,2,0,2,3};
Shader* shader;
Buffer* buffer;
Texture* texture;
Camera* camera = new Camera();

void PublicGame::preBoot()
{
	PublicGame::setGameName((int8*)"TestGame");
	PublicGame::setWindowSize(1280, 720);
}

void PublicGame::GameBoot()
{
    camera->setFieldForView();
    std::vector<SHADERLAYOUTTYPE> types;
    types.push_back(SHADERLAYOUTTYPE::FLOAT3);
    types.push_back(SHADERLAYOUTTYPE::FLOAT2);

    buffer = new Buffer(vertices, sizeof(vertices),indices, sizeof(indices));

    shader = new Shader(FileManager::get()->readShaderFile("resources/shader",true).data(),
                               FileManager::get()->readShaderFile("resources/shader",false).data());

    texture = new Texture(FileManager::get()->getAbsolutePath("resources/Disco-Dingo.jpg"),0);
    OpenGLUtils::setInt(shader->getOGLSID(),"texture1",0);

    Renderer::get().submit(buffer,shader,types,texture);

    model = glm::translate(model,glm::vec3(0.0f,0.0f,-2.0f));
}

void PublicGame::GameUpdate()
{
    Renderer::get().beginLevel(*camera);
    OpenGLUtils::setMat4(shader->getOGLSID(), "model", model);
    OpenGLUtils::setMat4(shader->getOGLSID(), "view", view);
    Renderer::get().endLevel();
}

void PublicGame::GameLevel()
{

}

int main()
{
    lunaLuxEngine::get()->runEngine(new PublicGame(),true);
}