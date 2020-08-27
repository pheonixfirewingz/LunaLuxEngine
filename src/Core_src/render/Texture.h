//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_TEXTURE_H
#define LUNALUXENGINE_TEXTURE_H
#include <string>
#include "Common/ITexture.h"

namespace LunaLuxEngine
{
    class Texture
    {
    private:
        ITexture *texture;
    public:

        Texture(std::string path, int id)
        {
            create(path,id);
        }

        void create(std::string, int);

        void bind();

        void unbind();
    };
}
#endif //LUNALUXENGINE_TEXTURE_H
