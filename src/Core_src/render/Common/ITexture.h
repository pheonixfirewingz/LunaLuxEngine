//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_ITEXTURE_H
#define LUNALUXENGINE_ITEXTURE_H
#include <string>
namespace LunaLuxEngine
{
    class ITexture
    {
    protected:
        unsigned int m_id_NOG;
    public:
        virtual void create(std::string path, int id) = 0;

        virtual void bind() = 0;

        virtual void unbind() = 0;
    };
}
#endif //LUNALUXENGINE_ITEXTURE_H
