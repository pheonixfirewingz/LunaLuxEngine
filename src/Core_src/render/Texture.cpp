//
// Created by luket on 27/08/2020.
//

#include "Texture.h"
#include "OpenGL/OpenGLTexture.h"

void LunaLuxEngine::Texture::create(std::string path, int id)
{
    texture = new OpenGLTexture();
    texture->create(path,id);
}

void LunaLuxEngine::Texture::bind()
{
    texture->bind();
}

void LunaLuxEngine::Texture::unbind()
{
    texture->unbind();
}
