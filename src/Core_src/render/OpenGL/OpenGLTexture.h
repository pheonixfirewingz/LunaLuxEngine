//
// Created by luket on 20/07/2020.
//

#ifndef LUNALUXENGINE_OPENGLTEXTURE_H
#define LUNALUXENGINE_OPENGLTEXTURE_H

#include <string>
#include "../Common/ITexture.h"
#include "glad.h"

namespace LunaLuxEngine
{
    class OpenGLTexture : public ITexture
    {
    private:
        unsigned int m_id;

        unsigned int load(std::string path);

    public:
        OpenGLTexture()
        {
            glEnable(GL_TEXTURE_2D);
        }

        void create(std::string path, int id) override;

        void bind() override;

        void unbind() override;
    };
}
#endif //LUNALUXENGINE_OPENGLTEXTURE_H
