//
// Created by luket on 27/08/2020.
//

#ifndef LUNALUXENGINE_OPENGLSHADERLAYOUT_H
#define LUNALUXENGINE_OPENGLSHADERLAYOUT_H
#include "../Common/IShaderLayout.h"

namespace LunaLuxEngine
{

    class OpenGLShaderLayout : public IShaderLayout
    {
    private:
        int m_count;
    public:
        void setupShaderLayout(std::vector<SHADERLAYOUTTYPE> vector) override;

        void bindLayoutToRenderer() override;

        void unbindLayoutToRenderer() override;
    };

}
#endif //LUNALUXENGINE_OPENGLSHADERLAYOUT_H
