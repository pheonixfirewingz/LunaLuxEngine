//
// Created by luket on 20/07/2020.
//

#include "OpenGLTexture.h"

OpenGLTexture::OpenGLTexture(std::string path)
{
    m_id = load(path);
}

unsigned int OpenGLTexture::getWidth()
{
    return m_width;
}


unsigned int OpenGLTexture::getHeight()
{
    return m_height;
}

unsigned int OpenGLTexture::getId()
{
    return m_id;
}

void OpenGLTexture::bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void OpenGLTexture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int OpenGLTexture::load(std::string path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    stbi_uc *data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    m_width = width;
    m_height = height;

    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4)
    {
        internalFormat = GL_RGBA8;
        dataFormat = GL_RGBA;
    }
    else if (channels == 3)
    {
        internalFormat = GL_RGB8;
        dataFormat = GL_RGB;
    }

    unsigned int result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    return result;
}