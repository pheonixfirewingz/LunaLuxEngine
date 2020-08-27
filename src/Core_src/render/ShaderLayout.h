//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_SHADERLAYOUT_H
#define LUNALUXENGINE_SHADERLAYOUT_H
#include "Common/IShaderLayout.h"
#include "OpenGL/OpenGLShaderLayout.h"
#include "Buffer.h"

namespace LunaLuxEngine
{

    class ShaderLayout
    {
    private:
        IShaderLayout* shaderLayout;
    public:
        ShaderLayout()
        {
            shaderLayout = new OpenGLShaderLayout();
        }

        ShaderLayout(std::vector<SHADERLAYOUTTYPE> types,Buffer* buffer)
        {
            shaderLayout = new OpenGLShaderLayout();
            buffer->bindV();
            setupShaderLayout(types);
            buffer->unBindV();
        }

        void setupShaderLayout(std::vector<SHADERLAYOUTTYPE>);

        virtual void bindLayoutToRenderer();

        virtual void unbindLayoutToRenderer();
    };

}
#endif //LUNALUXENGINE_SHADERLAYOUT_H
