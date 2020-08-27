//
// Created by luket on 20/07/2020.
//

#ifndef LUNALUXENGINE_OPENGLTEXTURE_H
#define LUNALUXENGINE_OPENGLTEXTURE_H

#include <string>
#include "glad.h"

class OpenGLTexture
{
public:

    unsigned int m_id, m_id_NOG, m_height, m_width;

    OpenGLTexture(std::string path,int id);

    unsigned int getWidth();

    unsigned int getHeight();

    void bind();

    void unbind();

private:
    unsigned int load(std::string path);
};


#endif //LUNALUXENGINE_OPENGLTEXTURE_H
