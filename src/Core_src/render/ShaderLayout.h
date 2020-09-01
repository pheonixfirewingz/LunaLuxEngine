//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_SHADERLAYOUT_H
#define LUNALUXENGINE_SHADERLAYOUT_H
#include "Common/IShaderLayout.h"
#include "Buffer.h"

namespace LunaLuxEngine
{

    class ShaderLayout
    {
    private:
        IShaderLayout* shaderLayout;
    public:
        ShaderLayout();

        ShaderLayout(std::vector<SHADERLAYOUTTYPE> types,Buffer* buffer);

        void setupShaderLayout(std::vector<SHADERLAYOUTTYPE>);

        void bindLayoutToRenderer();

        void unbindLayoutToRenderer();
    };

}
#endif //LUNALUXENGINE_SHADERLAYOUT_H
