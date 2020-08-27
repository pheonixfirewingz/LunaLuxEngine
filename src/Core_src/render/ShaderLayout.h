//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_SHADERLAYOUT_H
#define LUNALUXENGINE_SHADERLAYOUT_H
#include "Common/IShaderLayout.h"
#include "OpenGL/OpenGLShaderLayout.h"

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
        void setupShaderLayout(std::vector<SHADERLAYOUTTYPE>);

        virtual void bindLayoutToRenderer();

        virtual void unbindLayoutToRenderer();
    };

}
#endif //LUNALUXENGINE_SHADERLAYOUT_H
