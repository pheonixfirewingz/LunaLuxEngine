//
// Created by luket on 20/07/2020.
//

#include "OpenGLTexture.h"
#include "../Common/stb_image.h"

OpenGLTexture::OpenGLTexture(std::string path,int id)
{
    m_id = load(path);
    m_id_NOG = id;
}

unsigned int OpenGLTexture::getWidth()
{
    return m_width;
}


unsigned int OpenGLTexture::getHeight()
{
    return m_height;
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
    switch (m_id_NOG)
    {
        case 0:
            glActiveTexture(GL_TEXTURE0);
            break;
        case 1:
            glActiveTexture(GL_TEXTURE1);
            break;
        case 2:
            glActiveTexture(GL_TEXTURE2);
            break;
        case 3:
            glActiveTexture(GL_TEXTURE3);
            break;
        case 4:
            glActiveTexture(GL_TEXTURE4);
            break;
        case 5:
            glActiveTexture(GL_TEXTURE5);
            break;
        case 6:
            glActiveTexture(GL_TEXTURE6);
            break;
        case 7:
            glActiveTexture(GL_TEXTURE7);
            break;
        case 8:
            glActiveTexture(GL_TEXTURE8);
            break;
        case 9:
            glActiveTexture(GL_TEXTURE9);
            break;
        case 10:
            glActiveTexture(GL_TEXTURE10);
            break;
        case 11:
            glActiveTexture(GL_TEXTURE11);
            break;
        case 12:
            glActiveTexture(GL_TEXTURE12);
            break;
        case 13:
            glActiveTexture(GL_TEXTURE13);
            break;
        case 14:
            glActiveTexture(GL_TEXTURE14);
            break;
        case 15:
            glActiveTexture(GL_TEXTURE15);
            break;
        case 16:
            glActiveTexture(GL_TEXTURE16);
            break;
        case 17:
            glActiveTexture(GL_TEXTURE17);
            break;
        case 18:
            glActiveTexture(GL_TEXTURE18);
            break;
        case 19:
            glActiveTexture(GL_TEXTURE19);
            break;
    }
    unsigned int result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    return result;
}

